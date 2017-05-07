# MESO Project Template
Default folder structure and patch setup to base your projects on

# Folder Structure
- **Other** - Basically everything that doesn't fit the other folders on this folder level. If you need a place to put your Arduino code or whatever, this is it.
  - **Logs** - TTY Logs by vvvv can be found here for debugging purposes
  - **Scripts** - Useful scripts to help you with some tasks
  - **Thirdparty** - Thirdparty software that may be used within the project
- **Software** - Everything that is needed to run the patch
  - **Assets**
    - **Assets** - Assets that are being used within the project and are tracked in git
      - **PatchAssets** - Assets that are needes by the software like icons etc.
      - **ContentAssets** - Assets which are loaded by runtime from a externel source like a CMS
      - **FatAssets** - Assets that are to large to keep track of in git
    - **nodes** - Put any contributions and own stuff in here with respect to the folder naming conventions that vvvv would use within a pack or when cloning a template (i.e. _dx11, geom11, texture11, ..._)
      - **effects**
      - **modules**
      - **plugins**
    - **Patches** - All the patches that are part of the project. In this root folder, there ought to be root patches only.
      - **Subpatches** - All Subpatches go in here ... you might want to split these up for different patches (i.e. _RenderClient_ and _ControlClient_)
- **vvvv** - Put all vvvv versions in here that are in use by the projec

# How to use
Please download latest vvvv + addonpack and required packs and put it into the `vvvv`-folder, like so: `vvvv\vvvv_45beta34.2_x64`.
After it was put there, execute the `create vvvv start file.sh` script in the `Other\Scripts`-Folder to generate a default .bat-file for all the vvvv-versions inside the `vvvv`-folder to start the project from.

Open `vvvv\vvvv_45beta...\root.v4p` in vvvv and type **_"Software\nodes"_** in the rightmost IO Box to add the folder to the vvvv nodelist.

# Links
- **http://qfsm.sourceforge.net/** - Create and export automata code for vvvv
- **https://vvvv.org/contribution/vvvv-task-killer** - Handy taskbar tool to quickly kill the vvvv process by hitting Ctrl+Alt+V
- **https://vvvv.org/contribution/dds-converter** - Tool to batch convert textures to DDS
