//
//  ModalAlert.ccp
//
//  A Cocos2d-x v3 rewrite of my Cocos2d-Objc v3.5 rewrite of the Cocos2d-iPhone v2 ModalAlert class!
//  Displays custom cross-platform dialog boxes, which can be used instead of the native iOS alert views.
//
//  Originally sourced from https://rombosblog.wordpress.com/2012/02/28/modal-alerts-for-cocos2d/.
//
//  Copyright (c) 2016 - 2017 Ryan Bourne. All rights reserved.
//  https://www.ryanbournedev.wordpress.com & https://twitter.com/ryanbourne28
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#include "ModalAlert.h"

bool ModalAlert::init() {
  if (!Node::init()) return false;
  
  return true;
}

void ModalAlert::closeAlert(Sprite* dialog, Node* backing, Node* parent, const function<void()> &excBlk) {
  dialog->runAction(EaseSineInOut::create(EaseBackIn::create(ScaleTo::create(.5, 0))));
  backing->runAction(Sequence::create(FadeTo::create(.5, 0), CallFunc::create([&,backing,parent]() {
    backing->removeFromParent();
    if (excBlk != nullptr) {
      excBlk();
    }
  }),NULL));
}

void ModalAlert::makeNode(string msg, string boxFileName, Node* parent, int fntSize, string fntName, const function<void()> &btnPressed, string opt1, const function<void()> &opt1blk, string opt2, const function<void()> &opt2blk) {
  vSize = Director::getInstance()->getVisibleSize();
  ori = Director::getInstance()->getVisibleOrigin();
  
  // Add backing layer
  auto backing = LayerColor::create(Color4B(0, 0, 0, 0));
  this->addChild(backing);
  parent->addChild(this, 1000);
  
  // Create dialog box
  auto dialog = Sprite::createWithSpriteFrameName(boxFileName);
  dialog->setPosition(PerPoint(.5, .5));
  dialog->setOpacity(255);
  
  Size dialogBoxSize = dialog->getContentSize();
  
  // Create message label
  auto message = Label::createWithTTF(msg, fntName, fntSize);
  message->setHorizontalAlignment(TextHAlignment::CENTER);
  message->setVerticalAlignment(TextVAlignment::CENTER);
  message->setDimensions(dialogBoxSize.width*.9, dialogBoxSize.height*.55);
  message->setOverflow(Label::Overflow::SHRINK);
  dialog->addChild(message, 1);
  message->setPosition(dialogBoxSize.width*.5, dialogBoxSize.height*.6);
  
  auto opt1btn = Button::create("");
  opt1btn->setTitleText(opt1);
  opt1btn->setTitleFontName(fntName);
  opt1btn->setTitleFontSize(20);
  
  auto opt2btn = Button::create("");
  auto opt2exists = false;
  
  if (opt2.length() != 0) {
    opt2exists = true;
    
    opt2btn->setTitleText(opt2);
    opt2btn->setTitleFontName(fntName);
    opt2btn->setTitleFontSize(20);
    dialog->addChild(opt2btn);
    opt2btn->setPosition(Vec2(dialogBoxSize.width*.73, dialogBoxSize.height*.2));
    opt2btn->addTouchEventListener([&,btnPressed, opt1btn,opt2btn,dialog,backing,parent,opt2blk](Ref* sender, Widget::TouchEventType type) {
      if (type == Widget::TouchEventType::BEGAN && btnPressed != nullptr) {
        btnPressed();
      }
      
      if (type != Widget::TouchEventType::ENDED) {
        return;
      }
      
      opt1btn->setEnabled(false);
      opt2btn->setEnabled(false);
      
      // close alert
      closeAlert(dialog, backing, parent, opt2blk);
    });
  }
  
  dialog->addChild(opt1btn);
  opt1btn->setPosition(Vec2(opt2.empty() ? dialogBoxSize.width*.5 : dialogBoxSize.width*.27, dialogBoxSize.height*.2));
  opt1btn->addTouchEventListener([&,btnPressed,opt1btn,opt2exists,opt2btn,dialog,backing,parent,opt1blk](Ref* sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::BEGAN && btnPressed != nullptr) {
      btnPressed();
    }
    
    if (type != Widget::TouchEventType::ENDED) {
      return;
    }
    
    opt1btn->setEnabled(false);
    
    if (opt2exists) {
      opt2btn->setEnabled(false);
    }
    
    // close alert
    closeAlert(dialog, backing, parent, opt1blk);
  });
  
  backing->addChild(dialog,1);
  
  // Animate in layers
  backing->runAction(FadeTo::create(.5, 127.5));
  dialog->setScale(0);
  dialog->runAction(EaseSineInOut::create(EaseBackOut::create(ScaleTo::create(.5, 1))));
}

Node* ModalAlert::ask(string question, string boxFileName, Node* parent, int fntSize, string fntName, const function<void()> &btnPressed, const function<void()> &yes, const function<void()> &no) {
  auto modal = ModalAlert::create();
  modal->makeNode(question, boxFileName, parent, fntSize, fntName, btnPressed, "Yes", yes, "No", no);
  return modal;
}

Node* ModalAlert::confirm(string question, string boxFileName, Node* parent, int fntSize, string fntName, const function<void()> &btnPressed, const function<void()> &ok, const function<void()> &cancel) {
  auto modal = ModalAlert::create();
  modal->makeNode(question, boxFileName, parent, fntSize, fntName, btnPressed, "Ok", ok, "Cancel", cancel);
  return modal;
}

Node* ModalAlert::tell(string statement, string boxFileName, Node* parent, int fntSize, string fntName, const function<void()> &btnPressed, const function<void()> &ok) {
  auto modal = ModalAlert::create();
  modal->makeNode(statement, boxFileName, parent, fntSize, fntName, btnPressed, "Ok", ok, "", nullptr);
  return modal;
}

Vec2 ModalAlert::PerPoint(float x, float y) {
  return Vec2(ori.x+vSize.width*x, ori.y+vSize.height*y);
}
