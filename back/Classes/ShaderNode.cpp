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

#include "ShaderNode.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Node* ShaderNode::createScene()
{
	return ShaderNode::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool ShaderNode::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Node::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(ShaderNode::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	// add "ShaderNode" splash screen"
	/*auto sprite0 = Sprite::create("ShaderNode.png");
	if (sprite0 == nullptr)
	{
		problemLoading("'ShaderNode.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite0->setPosition(Vec2(visibleSize.width / 2 + origin.x + 150, visibleSize.height / 2 + origin.y + 150));

		// add the sprite as a child to this layer
		this->addChild(sprite0, 0);
	}

	auto sprite1 = Sprite::create("ShaderNode.png");
	if (sprite1 == nullptr)
	{
		problemLoading("'ShaderNode.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x - 200, visibleSize.height / 2 + origin.y - 200));
		sprite1->setScale(2, 2);
		sprite1->setColor(Color3B(0, 255, 0));

		// add the sprite as a child to this layer
		this->addChild(sprite1, 2);
	}*/

	GLenum error;

	m_pProgram = new GLProgram;

	m_pProgram->initWithFilenames("shaders/shader_0tex.vsh", "shaders/shader_0tex.fsh");
	error = glGetError();

	m_pProgram->bindAttribLocation("a_position", GLProgram::VERTEX_ATTRIB_POSITION);
	error = glGetError();

	m_pProgram->bindAttribLocation("a_color", GLProgram::VERTEX_ATTRIB_COLOR);
	error = glGetError();

	//m_pProgram->bindAttribLocation("a_texCoord", GLProgram::VERTEX_ATTRIB_TEX_COORD);
	//error = glGetError();

	m_pProgram->link();
	error = glGetError();

	m_pProgram->updateUniforms();
	error = glGetError();

	uniform_wvp_matrix = glGetUniformLocation(m_pProgram->getProgram(), "u_wvp_matrix");

	//uniform_sampler = glGetUniformLocation(m_pProgram->getProgram(), "sampler");

	//m_pTexture = Director::getInstance()->getTextureCache()->addImage("ShaderNode.png");

	//Director::getInstance()->setClearColor(Color4F(0, 1, 0, 0));

	return true;
}


void ShaderNode::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void ShaderNode::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
	//glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
	_customCommand.init(_globalZOrder, transform, flags); // カスタムコマンドで呼び出される関数を指定し、引数もセットで渡す
	_customCommand.func = CC_CALLBACK_0(ShaderNode::onDraw, this, transform, flags); // 描画コマンドをレンダラーに予約 
	renderer->addCommand(&_customCommand);
}

void ShaderNode::onDraw(const Mat4& transform, uint32_t flags) {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLenum error;

	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
	error = glGetError();

	m_pProgram->use();
	error = glGetError();

	//getGLProgram()->setUniformsForBuiltins(transform);

	Vec3 pos[4];
	Vec4 color[4];
	//Vec2 uv[4];
	const float x = 50.0f;
	const float y = 50.0f;



	pos[0] = Vec3(-x, -y, 0);
	pos[1] = Vec3(-x, y * 2, 0);
	pos[2] = Vec3(x, -y * 3, 0);
	pos[3] = Vec3(x * 4, y, 0);

	color[0] = Vec4(1, 0, 0, 1);
	color[1] = Vec4(1, 1, 0, 1);
	color[2] = Vec4(1, 0, 1, 1);
	color[3] = Vec4(1, 1, 1, 1);

	/*uv[0] = Vec2(0, 1);
	uv[1] = Vec2(0, 0);
	uv[2] = Vec2(1, 1);
	uv[3] = Vec2(1, 0);*/

	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, pos);

	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);

	//glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, uv);

	//glUniform1i(uniform_sampler, 0);
	//GL::bindTexture2D(m_pTexture->getName());

	/*for (int i = 0; i < 10; i++)
	{
		float _offset = 0.05f;
		pos[0].x += _offset; pos[0].y += _offset;
		pos[1].x += _offset; pos[1].y += _offset;
		pos[2].x += _offset; pos[2].y += _offset;
		pos[3].x += _offset; pos[3].y += _offset;

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}*/

	static float yaw = 0.0f;
	yaw += 0.01f;
	Mat4 matProjection;
	Mat4 matView;
	Mat4 matWVP;
	Mat4 matTrans, matScale, matRot, matWorld;

	matProjection = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

	matView = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Mat4::createTranslation(Vec3(visibleSize.width / 2 - 50, visibleSize.height / 2, 0), &matTrans);

	Mat4::createRotationY(yaw, &matRot);

	Mat4::createScale(Vec3(sin(yaw) * 4, sin(yaw) * 4, 1), &matScale);

	matWorld = matTrans * matRot * matScale;

	matWVP = matProjection * matView * matWorld;

	glUniformMatrix4fv(uniform_wvp_matrix, 1, GL_FALSE, matWVP.m);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);

	error = glGetError();
}