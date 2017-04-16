//
//  ModalAlert.h
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

#ifndef ModalAlert_h
#define ModalAlert_h

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;
using namespace ui;

class ModalAlert: public Node {
public:
  virtual bool init();
  
  void closeAlert(Sprite* dialog, Node* backing, Node* parent, const function<void()> &excBlk);
  
  void makeNode(string msg, string boxFileName, Node* parent, int fntSize, string fntName, const function<void()> &btnPressed, string opt1, const function<void()> &opt1blk, string opt2, const function<void()> &opt2blk);
  
  CREATE_FUNC(ModalAlert);
  
  static Node* ask(string question, string boxFileName, Node* parent, int fntSize, string fntName, const function<void()> &btnPressed, const function<void()> &yes, const function<void()> &no);
  
  static Node* confirm(string question, string boxFileName, Node* parent, int fntSize, string fntName, const function<void()> &btnPressed, const function<void()> &ok, const function<void()> &cancel);
  
  static Node* tell(string statement, string boxFileName, Node* parent, int fntSize, string fntName, const function<void()> &btnPressed, const function<void()> &ok);
  
  Vec2 PerPoint(float x, float y);
  
  Size vSize;
  Vec2 ori;
};

#endif /* ModalAlert_h */
