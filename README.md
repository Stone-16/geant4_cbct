<div align="center">
<h1>
  Geant4模拟CBCT实例
</h1>
</div>

# Geant4安装

> 由于Geant4在Windwos上不支持多线程，不推荐直接在Windows上安装，Windows平台推荐WSL2或VirutalBox等虚拟机。

1. 安装OpenGL、Qt5和Geant4

在项目根目录下运行``instal.sh``，自动安装

> 请确保网络状态良好，编译可能需要数十分钟。

```sh
sudo bash ./install.sh
```

2. 将Geant4添加至环境变量

```
echo 'source /geant4/geant4-install/bin/geant4.sh' >> ~/.bashrc
echo 'source /geant4/geant4-install/share/Geant4-11.0.4/geant4make/geant4make.sh' >> ~/.bashrc
source ~/.bashrc
```

P.S. 如果需要其他功能，如ROOT，请自行参考官网安装。


# Python重建

首先配置Python环境

```sh
conda create -n cbct python=3.10
conda activate cbct
conda install -c astra-toolbox astra-toolbox
python -m pip install -r requirements.txt
```

执行模拟

```sh
cd geant4
bash run.sh
cd ../python
python simulate_projection.py
```

重建

```sh
python reconstruction.py
```
