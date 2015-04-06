### PL2 Script Commands ###

Summary of commands used in Polygon Love 2 script files. This list is based on
the script comments and educated guesses. No empirical testing has been done
yet, and the author gives no guarantee that any of them is accurate or correct.

Conventions:
  * Commands are CaSe-SeNsItIvE.
  * Commands that take one or more arguments should be closed with a semicolon,
> > even if the arguments are empty. (Commas should remain, however.)
  * Calculating time in "frames" assumes a framerate of 60(?)fps.
  * A pound (#) character begins a comment which extends to the end of the line.
  * Labels are introduced with a colon and closed with a semicolon.

Format:
command

> "Mnemonic"
> Description of the command and its parameters.

#### Flow control ####

`%G<X>;`
> "Go"<br />
> Go to script X.

`%J<X>;`
> "Jump"<br />
> Jump to label X.

`%Q`
> "Quit"<br />
> Quit the game.

#### Text/game control ####

`%W<X>;`
> "Window"<br />
> Show/hide message window.

`%T<X>;`
> "Title"<br />
> Show/hide title logo (and adjust menu position).

`%w<X>;`
> "Wait"<br />
> Wait X frames.

`%n<X>;`
> "Name"<br />
> Set displayed character name to X.

`%K`
> "Keep"<br />
> Keep text window displayed until user input.

#### Variables ####

`%S<X>,<Y>,<Z>;`
> "Set"<br />
> Modify value in slot X using operator Y and operand Z.
> E.g. %S0,=,42; <- set value #0 to 42
> > %S1,+,5;  <- add 5 to value #1

`%E<X>,<Y>,<Z>,<W>;`

> "Evaluate"<br />
> Test value in slot X using operator Y and operand Z; jump to label W if true.

#### Menus ####

`%i<X>,<Y>;`
> "Item"<br />
> Add item to current menu with text X and label Y.

`%I`
> "Input"<br />
> Execute current menu and jump to label of selected item.

#### Models and animation ####

`%ml<X>,<Y>;`
> "Model Load"<br />
> Load model Y in slot X.

`%mb<X>,<Y>;`
> "Model Background"<br />
> Load background (room) model Y in slot X.

`%mm<X>,<Y>;`
> "Model Motion"<br />
> Animate model in slot X with animation Y.

`%mn<X>,<Y>;`
> "Model motioN"<br />
> Animate background model in slot X with animation Y.

`%mp<X>,<Y>;`
> "Model Position"<br />
> Move model in slot X to (named) position Y.

`%ma<X>,<Y>,<Z>;`
> "Model Add"<br />
> Add contents of model Z to sub-slot Y of model in slot X.

`%md<X>,<Y>;`
> "Model Delete"<br />
> Remove model in slot Y of character X.

`%mh<X>,<Y>,<Z>;`
> "Model H-mode"<br />
> Load/unload "H-mode" (partly removed) version of model in slot Y of character X.

`%mv<X>,<Y>;`
> "Model Visible"<br />
> Set visibility of model X to Y (0 = invisible, 1 = visible).

#### Lighting ####

`%lv<N>,<X>,<Y>,<Z>;`
> "Light Vertex"<br />
> Set position (vertex) of light N.

`%ld<N>,<R>,<G>,<B>;`
> "Light Diffuse"<br />
> Set diffuse color of light N to (R, G, B).

`%la<N>,<R>,<G>,<B>;`
> "Light Ambient"<br />
> Set ambient color of light N to (R, G, B).

`%ls<N>,<R>,<G>,<B>;`
> "Light Specular"<br />
> Set specular color of light N to (R, G, B).


`%le<N>,<X>;`
> "Light Enable"<br />
> Enable/disable light N.

#### Camera control ####

`%c<X>,<Y>;`
> "Camera"<br />
> Set camera to follow path X (and loop if Y?).

`%cp<X>;`
> "Camera Position"<br />
> Make camera look at position X.

`%cl<X>;`
> "Camera Lock"<br />
> Lock/unlock? camera. (Lock what? Disable user control?)

#### Graphics ####

`%g<X>;`
> "Graphic"<br />
> Display image X.

`%f<X>,<Y>,<Z>;`
> "Fade"<br />
> Fade (layer X?) to alpha level Y over Z frames.
> (Seems like X=0 -> 3D graphics, X=1 -> 2D graphics/overlay)

#### Music and sound effects ####

`%M<X>,<Y>;`
> "Music"<br />
> Play music X (fade for Y frames?).

`%MA<X>,<Y>;`
> "Media Audio"<br />
> Play looping sound effect X (fade for Y frames?).

`%MS<X>,<Y>;`
> "Media Sound"<br />
> Play sound effect X (fade for Y frames?).

`%o<X>;`
> "vOice"<br />
> Play voice file X.

`%oR<X>,<A>,<B>,<C>,<D>;`
> "vOice Repeating"<br />
> Set up repeating (random) voice between A and B. (Other parameters
> unknown yet.) Disabled if A<0 (or B<0?).