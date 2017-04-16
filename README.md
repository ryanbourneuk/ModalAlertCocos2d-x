# ModalAlert for Cocos2d-x

This class is the C++ rewrite for Cocos2d-x v3.14 of the rewrite for Cocos2d-objc v3 of the original ModalAlert class for the Objective-C Cocos2d-iPhone v2 game engine.

The original ModalAlert class is available to view here, and is what this class is based upon: https://rombosblog.wordpress.com/2012/02/28/modal-alerts-for-cocos2d/

It can be used as an alternative to the native alert view classes, specifically for iOS where the *UIAlertView* may not fit the look and style of your game.

## Here be dragons!

I am still learning C++ and this was one of the first classes I wrote as I started learning. It may have underlying issues which will be fixed later or not be as efficient as it could be. However, that's part of the learning process! Feel free to suggest improvements or fixes!

## How do I use it?!

The integration for this class is relatively straight forward, but does require a few steps in order to integrate it for simple use everywhere.

Firstly, you must download the *.cpp* and *.h* classes from this repository and place them into your project, and prepare the box sprite files which will be the images used for the dialog box.

The dimensions I have used (for reference) are:

  1x - 290 x 203
  
  2x - 581 x 407
  
  4x - 1000 x 700
  
The box sprite files should then be added to your project directory so that the game engine can select them based on the most appropriate resolution at runtime.

## Integration!

Once you have added the class files and the sprite files to your project, you need to make a few more minor changes.

  1. In *cocos2d.h*, you need to add `#include "ui/CocosGUI.h"`. This will allow you to access the ui namespace from anywhere you include *cocos2d.h*. You can probably only include the *CocosGUI.h* file in the *ModalAlert* class, however by placing it within *cocos2d.h* you can use it anywhere!
  2. If you have included the box sprite within a spritesheet instead of using separate sprites, you will need to change line 61 to use `createWithSpriteFrameName()` instead of `create()`.
  
You should then be able to include the *ModalAlert.h* file where you want to use a *ModalAlert*, and present them! An example would be:

```cpp
ModalAlert::tell(message, dialogImageName, parent, fontSize, fontName, buttonPressedBlock, dialogClosedBlock);
```

Where:
* '*message*' is the text you wish to show in the *ModalAlert*.
* '*dialogImageName*' is the filename of the dialog box you are using for the *ModalAlert*.
* '*parent*' is the node you wish to add the *ModalAlert* to, such as the layer you are currently viewing.
* '*fontSize*' is the size of the text you want to show.
* '*fontName*' is the file name of the font you wish to use in the *ModalAlert*.
* '*buttonPressedBlock*' is the callback used when a button is pressed. Use this to play a UI sound, such as one dictating that a button has been pressed.
* '*dialogClosedBlock*' is the callback used when the dialog box has been removed from the screen, and can be used to reallow input with objects on the layer the *ModalAlert* was added to.

Therefore, a completed example would be:

```cpp
// disable input before opening the ModalAlert
ModalAlert::tell("Alert!", "dialogBox.png", this, 25, "font.ttf", [&]() {
  // play sound when buttons are pressed
}, [&]() {
  // reenable input after the ModalAlert is closed here
});
```

If you choose to not use a callback when the *ModalAlert* buttons are pressed, simply pass `nullptr` instead of a block. Likewise, if you have no code to call when the *ModalAlert* disappears, pass `nullptr` instead of a block.

## Questions that aren't frequently asked but may be in the future!

### What platforms has this been tested on?

It has been tested and used extensively on iOS and Android, and should work on other platforms. Go play and find out!

### How do I add sound effects for when buttons are pressed?

Use the buttonPressed callback block, as shown in the example above.

Although it may seem tempting, **don't place them in the block you pass for when an option has been pressed!** The block is delayed until the alert has disappeared and will be really out of time with when the button was really pressed!

### I can still press on my background objects behind the alert! Explain! EXPLAIN!!

The ModalAlert does not swallow touches and this is left up to the individual to decide how they want to handle this. My personal choice is to disable any on screen interactive UI elements as the alert is presented. I do this personally by calling a function which will disable all of the buttons on the screen. I then call the function again to re-enable the buttons when the alert disappears. This is shown in the example above.

### Can I add more options to the ModalAlert view?

Absolutely! It should be easily expandable and that should be easy, however for my projects multiple options weren't needed so to keep it simple the code currently only supports up to two options.

### WHY THE TWO SPACE INDENTATION OH MY GOODNESS?!

Two spaces looks nicer than four spaces :)

### How can I ever repay you for this amazingness?!

If this has been useful to you, then great! Feel free to send me a tweet [@ryanbournedev](https://twitter.com/ryanbournedev) to let me know! If you really really liked it and a nice tweet just won't do, then feel free to help fund my hot chocolate cravings here: https://www.paypal.me/ryanbourne - although donations are not necessary! :) 
