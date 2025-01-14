<h1 align="center"><b>TA:K Enhanced</b></h1>
<p align="center">Adds new features and bugfixes to improve your TA:K experience.<br>
It's totally compatible with other 4.1bb versions.</p>

<h2 align="center"><b>Download & Install</b></h2>
<p align="center">Please refer to the last release here: <a href="https://github.com/riquems/tak-enhanced/releases">https://github.com/riquems/tak-enhanced/releases</a></p>

<h2 align="center"><b>Why TA:K Enhanced?</b></h1>
<div align="center">
<h3>Colorful HP Bars</h3>
<img src="imgs/colorful-hpbars.png"><br/>
Enjoy colorful HP Bars matching your team color!</div>
<br/>

<div align="center">
<h3>Building Rotation</h3>
<img src="imgs/rotate-buildings.gif" width="50%" height="60%"/><br/>
Use your mouse wheel to rotate buildings clockwise or counterclockwise! <br> Be aware you can only rotate them while they are being built.</div>
<br/>

<div align="center">
<h3>Melee Stuck Fix</h3>
<img src="imgs/before-melee-fix.gif" width="40%" height="40%"/>&nbsp<img src="imgs/after-melee-fix.gif" width="40%" height="40%"/><br>
Never have your melee units stuck again with the Melee Stuck Fix!
</div>
<br/>
<br/>

<div align="center"> 
<img src="imgs/badass-icon.png" width="64" height="64"><br/>
New badass icon</div>
<br/>

<p align="center">And much more:</p>

* Allows playing script maps in singleplayer.

* No-CD patch.

* Configurable unit limit (default 5000).

* Configurable PathFinding (default 100,000 path cycles).

* Game doesn't pause anymore when minimizing during SinglePlayer games.
* Uses Extreme AI.

## Game Changing Tweaks

- Wisps can now attack consistently.
- Mage Archer's 3rd weapon and Lighthouse's weapon now paralyze correctly.
- Elsin wave bugfix and Kirenna getting stuck when ordering her to attack.
- Thirsha's 2nd weapon and Centaur's weapon are now guided.
- Rolling Towers aren't capturable.
- Knights aren't freezeable.
- Fire Demon's attack delay against moving targets is gone.
- Acolyte and Weather Witch 1st and 2nd weapon have been swapped.


<h2 align="center"><b>Introduction to the Launcher</b></h2>
<br>

<div align="center">
  <img src="imgs/main.png"/><br>
  The main tab<br>
  It contains general tweaks of interest for gameplay.
</div>

<br>

<div align="center">
  <img src="imgs/presets.png"/><br>
  Preset Picker<br>
  Load your mod configuration for best experience!
</div>

<br>

<div align="center">
  <img src="imgs/game-options.png" /><br/>
  Game Options<br> Allows you to see your enemy's HP and tweak friendly fire options!
</div>

<br>

<div align="center">
  <img src="imgs/keybindings.png"/><br>
  Keybindings<br>
  Allows tweaking shortcuts for new commands introduced, such as SelectBuilding, RotateBuilding and SetUnitStance.
</div>

<br>

## Detailed Log

#### Game

- The game now saves your unit limit value used in your previous multiplayer match properly.
- Some screen changes will be faster now.

#### Aramon
- Fixed Elsin wave which would stop working for the rest of the match.
- Fixed Mage Archer paralyze weapon, adjusted for 2s stuns.
- Fixed Knight being freezable.
- Swapped Acolyte 1st and 2nd weapon.

#### Taros
- Fixed Fire Demon's attack delay against flying/moving units.
- Fixed Fire Mage first attack not hitting goblins.
- Swapped Weather Witch 1st and 2nd weapon.

#### Veruna
- Fixed Kirenna attack delays where you needed to double click in order to her start attacking.
- Catapult now shoots faster (and moving units) but is more imprecise (like aramon catapult)
- Fixed Centaur weapon not being guided.
- Fixed Lighthouse paralyze weapon, adjusted for 0.5s stuns.

#### Zhon
- Fixed Thirsha 2nd weapon not being guided.
- Adjusted Thirsha 2nd weapon velocity to match previous velocity (before being guided).
- Fixed Wisp not attacking consistently.
- Giant Orm doesn't do enourmous damage against undead units anymore.

#### Creon
- Fixed Gate not being targetted by units automatically.
- Fixed Creon Chief paralyze weapon, adjusted for 10s stuns.

#### Animals
- Fixed Deer water multiplier typo in fbi.
- Fixed Buck water multiplier typo in fbi.
- Fixed Saber Tooth Tiger road multiplier typo in fbi.

<details>
<summary>Even more detailed changes</summary>

<pre>v1.0 - Initial Release

+ Addition
- Removal
~ Modified
* Small description for complex changes.

* Badass Icon
* Command line params allowed
* No-CD
* 5000 Max Units
* Enhanced Pathfinding
* No pause when minimize or unfocus
* Extreme AI as default
* Game now saves previous unit limit used in multiplayer matches
* Some screen changes will be faster

TAKEnhanced.hpi/
scripts/

araking.cob
  * Fixed Elsin wave which would stop working for the rest of the match.
arapries.cob
  * Swapped 1st and 2nd weapon.

vermage.cob
  * Fixed Kirenna attack delays where you needed to double click in order to her start attacking.

tarmage.cob
  * Changed the piece attack is fired from.
tarwitch.cob
  * Swapped 1st and 2nd weapon.

unitscb/

araat.fbi
  + immunetoparalyzer = 1;
arabow.fbi
    weapon3
    ~ default = <s>1</s> ⇒ 57; // ~2s paralyze
aracastl.fbi
  + immunetoparalyzer = 1;
aradrag.fbi
  + immunetoparalyzer = 1;
aragod.fbi
  + immunetoparalyzer = 1;
aragren.fbi
    weapon3
    - dragon = 0;
    - factory = 0;
    - fort = 0;
    - god = 0;
    - monarch = 0;
    - naval = 0;
araking.fbi
  + immunetoparalyzer = 1;
arakeep.fbi
  - canattack = 1;
  + immunetoparalyzer = 1;
aralode.fbi
  + immunetoparalyzer = 1;
aramana.fbi
  + immunetoparalyzer = 1;
arangate.fbi
  + immunetoparalyzer = 1;
arapal.fbi
  + cantbefrozen = 1;
arapries.fbi
  * Swapped 1st and 2nd weapon
arassh.fbi
  + immunetoparalyzer = 1;
arasiege.fbi
  + cantbecaptured = 1;
  + immunetoparalyzer = 1;
aratrans.fbi
  + immunetoparalyzer = 1;
aratre.fbi
  + immunetoparalyzer = 1;
arawall.fbi
  + immunetoparalyzer = 1;
arawar.fbi
  + immunetoparalyzer = 1;

npcbotl.fbi
  + immunetoparalyzer = 1;
npcflag.fbi
  + immunetoparalyzer = 1;
npcrixx.fbi
  + immunetoparalyzer = 1;
npctemp.fbi
  + immunetoparalyzer = 1;
npctemp2.fbi
  + immunetoparalyzer = 1;
npcthesh.fbi
  + immunetoparalyzer = 1;

tarcage.fbi
  + immunetoparalyzer = 1;
tarcastl.fbi
  + immunetoparalyzer = 1;
tardrag.fbi
  + immunetoparalyzer = 1;
tardung.fbi
  + immunetoparalyzer = 1;
targod.fbi
  + immunetoparalyzer = 1;
tarhell.fbi
  + immunetoparalyzer = 1;
tarlode.fbi
  + immunetoparalyzer = 1;
tarmana.fbi
  + immunetoparalyzer = 1;
tarnecro.fbi
  + immunetoparalyzer = 1;
tarngate.fbi
  + immunetoparalyzer = 1;
tarsh.fbi
  + immunetoparalyzer = 1;
tarwall.fbi
  + immunetoparalyzer = 1;
tarwitch.fbi
  * Swapped 1st and 2nd weapon

verasy.fbi
  + immunetoparalyzer = 1;
verat.fbi
  + immunetoparalyzer = 1;
vercastl.fbi
  + immunetoparalyzer = 1;
vercen.fbi
    weapon1
    + turnrate = 180;
verdrag.fbi
  + immunetoparalyzer = 1;
verflag.fbi
  + immunetoparalyzer = 1;
verfltwr.fbi
  + immunetoparalyzer = 1;
vergod.fbi
  + immunetoparalyzer = 1;
verharp.fbi
  + immunetoparalyzer = 1;
verkeep.fbi
  + immunetoparalyzer = 1;
verlight.fbi
  + immunetoparalyzer = 1;
    weapon1
    ~ default = <s>1</s> ⇒ 15; // ~0.5s paralyze
verlode.fbi
  + immunetoparalyzer = 1;
vermage.fbi
  + immunetoparalyzer = 1;
verman.fbi
  + immunetoparalyzer = 1;
vermana.fbi
  + immunetoparalyzer = 1;
vermort.fbi
  + immunetoparalyzer = 1;
verngate.fbi
  + immunetoparalyzer = 1;
verpill.fbi
  + immunetoparalyzer = 1;
verpult.fbi
    weapon1
    + aimtolerance = 1024;
verscout.fbi
  + immunetoparalyzer = 1;
vertower.fbi
  + immunetoparalyzer = 1;
vertrans.fbi
  + immunetoparalyzer = 1;
vertre.fbi
  + immunetoparalyzer = 1;
verwall.fbi
  + immunetoparalyzer = 1;

zondrag.fbi
  + immunetoparalyzer = 1;
zonfire.fbi
  + immunetoparalyzer = 1;
zonflies.fbi
    weapon1
    + aimtolerance = 1024;
zonamoe.fbi
    weapon1
    + undead = 0.04;
zonglyph.fbi
  + immunetoparalyzer = 1;
zongod.fbi
  + immunetoparalyzer = 1;
zonhunt.fbi
  + immunetoparalyzer = 1;
    weapon2
    + turnrate = 180;
    ~ weaponvelocity = <s>500</s> ⇒ 480;
zonhurt.fbi
  + immunetoparalyzer = 1;
    weapon2
    + turnrate = 180;
    ~ weaponvelocity = <s>500</s> ⇒ 480;
zonlode.fbi
  + immunetoparalyzer = 1;
zonmana.fbi
  + immunetoparalyzer = 1;

creacad.fbi
  + immunetoparalyzer = 1;
creaeri.fbi
  + immunetoparalyzer = 1;
crebomb.fbi
  + immunetoparalyzer = 1;
crechie.fbi
    weapon3
    ~ default = <s>1</s> ⇒ 286; // ~10s
cregate.fbi
  + immunetoparalyzer = 1;
  + shootme = 1; 
cregatl.fbi
  + immunetoparalyzer = 1;
cregod.fbi
  + immunetoparalyzer = 1;
creiron.fbi
  + immunetoparalyzer = 1;
crelode.fbi
  + immunetoparalyzer = 1;
cremana.fbi
  + immunetoparalyzer = 1;
crenavy.fbi
  + immunetoparalyzer = 1;
crepris.fbi
  + immunetoparalyzer = 1;
cresage.fbi
  + immunetoparalyzer = 1;
cresmit.fbi
  + immunetoparalyzer = 1;
crester.fbi
  + immunetoparalyzer = 1;
cresubm.fbi
  + immunetoparalyzer = 1;
crewall.fbi
  + immunetoparalyzer = 1;

lifdeer.fbi
  ~ <s>watermultipliser</s> ⇒ watermultiplier
lifdeer2.fbi
  ~ <s>watermultipliser</s> ⇒ watermultiplier
lifsaber.fbi
  ~ <s>admultiplier</s> ⇒ roadmultiplier
</pre>
</details>
<br/>

## Important notes

- TA:K Enhanced is a series of improvements, and aims to be a must have in future TA:K competitive or non competitive matches, because of its potential.
- Watch out for mod conflicts.
- Watch out enabling patches and not adding corresponding .hpis files. Your game will crash! Some of them are dependent of these .hpis, so please always use one of them. Here is what is dependent on what:

- "Colorful HP Bars" feature needs Colorful HP Bars.hpi
- "Melees Stuck Fix" feature needs Melees Stuck Fix.hpi

## Credits

Paladin for many findings and ideas. Most of his contributions can be found here: https://kingdoms.catsboard.com/t1445-patch-bugs-balance-improvements  
WhiteHammer for ExtremeAI  
WL- Albino for tests and time.  
Kronos for testing and ideas.