![Screenshot_20241130_171351](https://github.com/user-attachments/assets/c3e4c61c-6833-4c69-80fb-3bf89cd7c7a5)
## Thy first raytracer
a great mathematics project based on random googled facts to make objects, all the formulas are taken from wikipedia, or just derived them ourselves
# 42 Minirt
- we got 125 point on the project, it supports multiple lightsources, has uv mapping for the supported objects which allow textures and the tiled pattern.
- the window is resizeable but slow, as the graphics library doesnt really allow us to have proper shaders so CPU abuse is expected, not even -Ofast was able to save us
- Some scenes are provided that we used for evaluation or that just looked good
# To run it yourself
- if it complains at compilation, remove WWW from the makefiles, some compilers have different standards for these
```
git clone <repo>
make # for macos
make wsl # for linux or windows wsl
./minirt <scene>
```
# Some pretty imigary
![Screenshot_20241130_171002](https://github.com/user-attachments/assets/9a93612c-1741-4d44-b50d-697c433b1749)
![Screenshot_20241130_170912](https://github.com/user-attachments/assets/455e4498-839c-4f86-aa6e-c0bd5a1d544a)
![Screenshot_20241130_170842](https://github.com/user-attachments/assets/5f9595ca-857e-4d7e-9540-d61006b7b18a)
![Screenshot_20241130_170810](https://github.com/user-attachments/assets/47b17f85-70ec-4043-802f-3482c386db5e)
![Screenshot_20241130_170740](https://github.com/user-attachments/assets/7160cc56-fce8-4023-aa22-4e24d69fc4bb)
