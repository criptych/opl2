### OPL2 Lua Scripting Interface ###

OPL2 replaces the original game script with Lua, a free, fast, and powerful
scripting language already used in many other applications and games. (In the
future an interpreter for the original scripts may be included, but there are
no such plans yet.) This page summarizes the objects and commands exposed to
OPL2 scripts. Information about general Lua syntax can be found at
[Lua.org](http://www.lua.org/manual/5.1/).

#### Functions ####

The following functions in the `pl2` module control the story flow and timing.

_bool_` = pl2.play(`_chan_`, `_name_`)`

> Plays a named sound on the specified channel. _chan_ must be a number from 1
> to 4, or one of the strings "voice", "sound", "bgsound", or "music". Returns
> `true` if the sound was loaded and played successfully.

`pl2.showText(`_string_`)`

> Displays text in the dialog box at the bottom of the screen. This function
> does not return until the player has dismissed the text (with the Enter or
> Return keys).

_sel_` = pl2.showMenu(`_table_`)`

> Displays a menu with up to 8 choices. Items beginning with an asterisk
> ("`*`") are disabled. Returns the index of the selected item, or `nil` if
> the menu was cancelled.

`pl2.wait(`_sec_`)`

> Waits _sec_ seconds before continuing. (Text/menus only; the scene and
> animations, etc. will continue during this time.) This can be used to e.g.
> complete a fade before changing character models or displaying text.

#### Objects ####

The following functions return objects used to control scene elements.

_camera_` = pl2.camera(`_n_`)`

> Returns a "camera" object. _n_ must be an integer from 1 to 2. Cameras
> define the player's viewpoint in the scene. Although two cameras are
> available per the original script, currently only the first may be used.

_character_` = pl2.char(`_n_`)`

> Returns a "character" object. _n_ must be an integer from 1 to 4. Characters
> may have attached up to 16 models, plus an animation and a transform.

_layer_` = pl2.layer(`_n_`)`

> Returns a "layer" object. _n_ must be an integer from 1 to 2. Layers control
> scene fading, specifically the background (3D) and foreground (2D) layers.

_light_` = pl2.light(`_n_`)`

> Returns a "light" object. _n_ must be an integer from 1 to 4. Lights provide
> lighting to the scene, and can be set to various colors. The original script
> used only two lights (confirm?), but four are available for convenience.

The following global objects are defined by default:
```
camera = pl2.camera(1)

imo = pl2.char(1)       -- little sister
ani = pl2.char(3)       -- big brother
room = pl2.char(4)      -- background/scenery

back = pl2.layer(1)     -- 3D fader
fore = pl2.layer(2)     -- 2D fader

light1 = pl2.light(1)
light2 = pl2.light(2)
```

When the script starts, all characters are empty (no attached models,
animations, or transforms), both faders are blacked out, and all lights are off.

#### Camera Methods ####

`camera:setEye(`_x_`, `_y_`, `_z_`)`

> Places the camera (thus the viewer's "eye") at the specified position.

_x_`, `_y_`, `_z_` = camera:getEye()`

> Returns the current position of the camera.

`camera:setFocus(`_x_`, `_y_`, `_z_`)`

> Aims the camera toward the specified position.

_x_`, `_y_`, `_z_` = camera:getFocus()`

> Returns the current focus of the camera.

`camera:setUp(`_x_`, `_y_`, `_z_`)`

> Sets the camera's up-vector. You won't normally need to use this.

_x_`, `_y_`, `_z_` = camera:getUp()`

> Returns the current up-vector of the camera.

`camera:setFov(`_fov_`)`

> Sets the camera's field-of-view, in degrees. This can be used for e.g.
> fisheye effects.

_x_`, `_y_`, `_z_` = camera:getUp()`

> Returns the current field-of-view of the camera, in degrees.

_bool_` = camera:setPath(`_name_`, `_loop_`)`

> Makes the camera follow a named path, looping if _loop_ is true. Returns
> `true` if the path was loaded successfully.

_bool_` = camera:setPoint(`_name_`)`

> Attaches a named transform to the camera. Returns `true` if the transform
> was found.

#### Character Methods ####

_bool_` = character:setModel(`_n_`, `_name_`)`

> Attaches a model to the character in slot _n_ (1 to 16). Returns `true` if
> the model was loaded successfully.

_bool_` = character:setModels(`_table_`)`

> Attaches a set of models to the character. Similar to:
```
for i = 1, 16 do
    character:setModel(i, table[i])
end
```
> Returns `true` only if all of the given models were loaded successfully, but
> will continue trying to load the rest even if one fails.

_bool_` = character:setAnim(`_name_`)`

> Attaches an animation to the character. The animation is applied to all
> models attached to the character. Returns `true` if the animation was loaded
> successfully.

_bool_` = character:setPoint(`_name_`)`

> Attaches a named transform to the character. Returns `true` if the transform
> was found.

`character:setVisible(`_bool_`)`

> Show or hide the character.

_bool_` = character:getVisible()`

> Returns whether the character is currently visible.

`character:setName(`_name_`)`

> Sets the name of the character. This name is displayed with the character's
> dialog (see below).

_string_` = character:getName()`

> Returns the current name of the character.

`character:setBlack(`_bool_`)`

> Sets whether the character appears blacked out. This can be used to show the
> male character as a silhouette. (This is an extension to the original script
> language.)

_bool_` = character:getBlack()`

> Returns whether the character is currently blacked out.

`character:clear()`

> Resets the character to its initial state.

#### Layer Methods ####

`layer:fade(`_lev_`, `_dur_`)`

> Fades the layer to level _lev_ over a period of _dur_ seconds. _lev_ may be
> a number (possibly fractional) between 0 and 1: at 0, the layer will be
> invisible (blacked out); at 1, the layer is completely visible.

#### Light Methods ####

`light:setPosition(`_x_`, `_y_`, `_z_`)`

> Sets the position of the light.

_x_`, `_y_`, `_z_` = light:getPosition()`

> Returns the current position of the light.

`light:setAmbient(`_r_`, `_g_`, `_b_`, `_a_`)`

> Sets the ambient color of the light.

_r_`, `_g_`, `_b_`, `_a_` = light:getAmbient()`

> Returns the current ambient color of the light.

`light:setDiffuse(`_r_`, `_g_`, `_b_`, `_a_`)`

> Sets the diffuse color of the light.

_r_`, `_g_`, `_b_`, `_a_` = light:getDiffuse()`

> Returns the current diffuse color of the light.

`light:setSpecular(`_r_`, `_g_`, `_b_`, `_a_`)`

> Sets the specular color of the light.

_r_`, `_g_`, `_b_`, `_a_` = light:getSpecular()`

> Returns the current specular color of the light.

`light:setEnabled(`_bool_`)`

> Enables or disables the light.

_bool_` = light:getEnabled()`

> Returns whether the light is currently enabled.

