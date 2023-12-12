import subprocess
import numpy as np
from tqdm import tqdm

angles_num = 360
angles = np.linspace(0, 360, angles_num , False)

with open('../geant4/build/run.mac', 'w', encoding='utf-8') as f:
    # f.write('/run/numberOfThreads 4\n')
    f.write('/run/initialize\n')
    f.write('/run/printProgress 1000000\n')
    f.write('/gps/verbose 0\n')
    f.write('/gps/particle gamma\n')
    f.write('/gps/pos/type Plane\n')
    f.write('/gps/pos/shape Rectangle\n')
    f.write('/gps/pos/halfx 0.025 mm\n')
    f.write('/gps/pos/halfy 0.025 mm\n')
    f.write('/gps/pos/centre 0. 0. -150. mm\n')
    f.write('/gps/ang/type iso\n')
    f.write('/gps/ang/maxtheta 6.8 deg\n')
    f.write('/gps/ene/type Arb\n')
    f.write('/gps/hist/file ../spectrum/160.txt\n')
    f.write('/gps/hist/inter Lin\n')
    f.write('/analysis/setFileName ../../output/background.root\n')
    f.write('/run/beamOn 10000000\n')
process = subprocess.Popen('cd ~/geant4_cbct/1_cbct/geant4/build && ./CBCT run.mac > log.txt', shell=True)
process.wait()

# geant模拟
for i in tqdm(range(angles_num), desc='Simulating'):
    with open('../geant4/build/run.mac', 'w', encoding='utf-8') as f:
        f.write(f'/CBCT/det/setPhantomRotation {angles[i]} deg\n')
        # f.write('/run/numberOfThreads 4\n')
        f.write('/run/initialize\n')
        f.write('/run/printProgress 1000000\n')
        f.write('/gps/verbose 0\n')
        f.write('/gps/particle gamma\n')
        f.write('/gps/pos/type Plane\n')
        f.write('/gps/pos/shape Rectangle\n')
        f.write('/gps/pos/halfx 0.025 mm\n')
        f.write('/gps/pos/halfy 0.025 mm\n')
        f.write('/gps/pos/centre 0. 0. -150. mm\n')
        f.write('/gps/ang/type iso\n')
        f.write('/gps/ang/maxtheta 6.8 deg\n')
        f.write('/gps/ene/type Arb\n')
        f.write('/gps/hist/file ../spectrum/160.txt\n')
        f.write('/gps/hist/inter Lin\n')
        f.write('/analysis/setFileName ../../output/{:04d}.root\n'.format(i))
        f.write('/run/beamOn 10000000\n')
    process = subprocess.Popen('cd ~/geant4_cbct/1_cbct/geant4/build && ./CBCT run.mac > log.txt', shell=True)
    process.wait()
