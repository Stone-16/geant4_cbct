import os
import numpy as np
import uproot
import astra
from tqdm import tqdm
import matplotlib.pyplot as plt


def gen_pr_2d(data, detector_num_x, detector_num_y, pixel_size):
    pr = np.zeros((detector_num_y, detector_num_x))
    detector_size_x = detector_num_x * pixel_size[0]
    detector_size_y = detector_num_y * pixel_size[1]
    x_i = np.floor((data['PosX'] + detector_size_x / 2.0) / pixel_size[0]).astype(int)
    y_i = np.floor((detector_size_y / 2.0 - data['PosY']) / pixel_size[1]).astype(int)
    index = (x_i >= 0) & (y_i >= 0) & (x_i < detector_num_x) & (y_i < detector_num_y)
    x_i = x_i[index]
    y_i = y_i[index]
    np.add.at(pr, (y_i, x_i), 1)
    return pr

def root2pr(root_path, detector_num_x, detector_num_y, pixel_size):
    file = uproot.open(root_path)
    singles = file['CBCT;1']
    data = singles.arrays(['EventID', 'PosX', 'PosY', 'PosZ', 'Edep'], library="pd")
    pr = gen_pr_2d(data, detector_num_x, detector_num_y, pixel_size)
    return pr

def load_pr(pr_dir, detector_num_x, detector_num_y, pixel_size):
    files = sorted(os.listdir(pr_dir))
    background = root2pr(os.path.join(pr_dir, files[-1]), detector_num_x, detector_num_y, pixel_size)
    files = files[:-1]
    files_num = len(files)
    pr = []
    for i in tqdm(range(files_num), desc='Loading projections'):
        pr.append(root2pr(os.path.join(pr_dir, files[i]), detector_num_x, detector_num_y, pixel_size))
    pr = np.array(pr)
    pr = -np.log(pr / background)
    pr = np.transpose(pr, (1, 0, 2))
    return np.array(pr)

if __name__ == '__main__':
    angles_num = 360
    distance_source_center = 150
    distance_center_detector = 150
    detector_num_x = 50
    detector_num_y = 50
    pixel_size = [1, 1]
    det_spacing_x = 1
    det_spacing_y = 1

    pr = load_pr('../output', detector_num_x, detector_num_y, pixel_size)
    np.save('pr.npy', pr)
    # pr = np.load('pr.npy')

    assert angles_num == pr.shape[1], '投影数目不一致'

    angles = np.linspace(0, 2 * np.pi, angles_num, False)
    vec_astra = np.zeros((angles.shape[0], 12),dtype=float)
    vec_astra[:, 0] = -distance_source_center * np.sin(angles)
    vec_astra[:, 1] = 0
    vec_astra[:, 2] = -distance_source_center * np.cos(angles)
    vec_astra[:, 3] = distance_source_center * np.sin(angles)
    vec_astra[:, 4] = 0
    vec_astra[:, 5] = distance_source_center * np.cos(angles)
    vec_astra[:, 6] = det_spacing_x * np.cos(angles)
    vec_astra[:, 7] = 0
    vec_astra[:, 8] = -det_spacing_x * np.sin(angles)
    vec_astra[:, 9] = 0
    vec_astra[:, 10] = det_spacing_y
    vec_astra[:, 11] = 0

    proj_geom = astra.create_proj_geom('cone_vec', 50, 50, vec_astra)
    proj_id = astra.data3d.create('-sino', proj_geom, pr)

    # Create a data object for the reconstruction
    vol_geom = astra.create_vol_geom(20, 20, 20)
    rec_id = astra.data3d.create('-vol', vol_geom)

    cfg = astra.astra_dict('SIRT3D_CUDA')
    cfg['ReconstructionDataId'] = rec_id
    cfg['ProjectionDataId'] = proj_id

    # Create the algorithm object from the configuration structure
    alg_id = astra.algorithm.create(cfg)

    astra.algorithm.run(alg_id, 150)

    # Get the result
    rec = astra.data3d.get(rec_id)
    print(rec.shape)
    plt.figure()
    plt.imshow(rec[:, 10, :], cmap='gray')
    plt.savefig('fig1.png')
    plt.figure()
    plt.imshow(rec[:, :, 4], cmap='gray')
    plt.savefig('fig2.png')
    plt.figure()
    plt.imshow(rec[:, :, 14], cmap='gray')
    plt.savefig('fig3.png')

    # Clean up. Note that GPU memory is tied up in the algorithm object,
    # and main RAM in the data objects.
    astra.algorithm.delete(alg_id)
    astra.data3d.delete(rec_id)
    astra.data3d.delete(proj_id)

