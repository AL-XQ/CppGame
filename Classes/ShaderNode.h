/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class ShaderNode : public cocos2d::Node
{
public:
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(ShaderNode);
	// 関数宣言
	void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags);
	void onDraw(const cocos2d::Mat4& transform, uint32_t /*flags*/);
	// 変数宣言
	cocos2d::GLProgram* m_pProgram;

	//int uniform_sampler;
	//cocos2d::Texture2D* m_pTexture;

	int uniform_wvp_matrix;

	int counter = 0;

	// カスタムコマンド
	cocos2d::CustomCommand _customCommand;

	cocos2d::Vec3 pos[6];
	cocos2d::Vec4 color[6];
	cocos2d::Vec2 uv[6];
	cocos2d::Mat4 matWVP;
};

#endif // __HELLOWORLD_SCENE_H__
