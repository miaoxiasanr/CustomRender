#include "RenderWidget.h"
#include "LoadModel.h"

vector2<float> MousePos;
Camera MyCamera(DefaultCameraLocation);
bool FirstMouse = true;
float LastX = Default_Width / 2;
float LastY = Default_Height / 2;
int CurrdeltaTime = 0;
int CurrlastFrame = 0;
float deltaTime = 0.f;

RenderWidget::RenderWidget(QWidget *parent)
	: QWidget(parent),Width(Default_Width),Height(Default_Height)
{
	ui.setupUi(this);
	this->grabKeyboard();
	setFixedSize(Default_Width, Default_Height);
	connect(&timer, &QTimer::timeout, this, &RenderWidget::Render);
	timer.start(1);//1毫秒更新一次

	//shadersetting
	bfsShader = new Blinn_PhongfsShader;

	bfsShader->DiffuseTexture = Texture("../Texture/container2.png");
	bfsShader->SpecularTexture = Texture("../Texture/container2_specular.png");
	bfsShader->light1.ambient = vector3f(0.2f, 0.2f, 0.2f);
	bfsShader->light1.diffuse = vector3f(0.5f, 0.5f, 0.5f);
	bfsShader->light1.specular = vector3f(1.0f, 0.0f, 0.0f);
	bfsShader->light1.constant = 1.f;
	bfsShader->light1.linear = 0.09f;
	bfsShader->light1.quadratic = 0.032f;

	pfsShader = new PhongfsShader;
	pfsShader->DiffuseTexture = Texture("../Texture/container2.png");
	pfsShader->SpecularTexture = Texture("../Texture/container2_specular.png");
	pfsShader->light1.ambient = vector3f(0.2f, 0.2f, 0.2f);
	pfsShader->light1.diffuse = vector3f(0.5f, 0.5f, 0.5f);
	pfsShader->light1.specular = vector3f(1.0f, 1.0f, 1.0f);
	pfsShader->light1.constant = 1.f;
	pfsShader->light1.linear = 0.09f;
	pfsShader->light1.quadratic = 0.032f;

	lfsShader = new LambertfsShader;
	lfsShader->DiffuseTexture = Texture("../Texture/container2.png");
	lfsShader->light1.ambient = vector3f(0.2f, 0.2f, 0.2f);
	lfsShader->light1.diffuse = vector3f(0.5f, 0.5f, 0.5f);
	lfsShader->light1.diffuse = vector3f(1.0f, 1.0f, 1.0f);



	vsShader.model = Translate(vsShader.model, vector3f(0.0f, 0.0f, -2.f));
	//vsShader.model = RotateY(vsShader.model, 45.f);
	
	
	vsShader1.model = Translate(vsShader1.model, vector3f(.0f, 0.0f, -2.f));
	vsShader2.model = Translate(vsShader2.model, vector3f(.0f, 0.0f, -2.f));
	
	LightfsShader = new FragmentShader;
	//LightvsShader.model = RotateX(LightvsShader.model, 45.f);

	LightvsShader.model = Scale(LightvsShader.model, vector3f(0.1f, 0.1f, 0.1f));
	LightvsShader.model = Translate(LightvsShader.model, DefaultLightPosition);
}

void RenderWidget::mouseMoveEvent(QMouseEvent* event)
{
	QPoint pos = event->pos();
	MousePos.x = pos.x();
	MousePos.y = pos.y();

	

}

void RenderWidget::keyPressEvent(QKeyEvent* event)
{

	switch (event->key())
	{
		case Qt::Key_W:
		{
			MyCamera.ProcessKeyboard(Camera_Movement::FORWARD, 1/deltaTime);
			break;
		}
		case Qt::Key_S:
		{
			MyCamera.ProcessKeyboard(Camera_Movement::BACKWARD, 1/deltaTime);
			break;
		}
		case Qt::Key_A:
		{
			MyCamera.ProcessKeyboard(Camera_Movement::LEFT, 1/deltaTime);
			break;
		}
		case Qt::Key_D:
		{
			MyCamera.ProcessKeyboard(Camera_Movement::RIGHT, 1/deltaTime);
			break;
		}
	}
}

void RenderWidget::wheelEvent(QWheelEvent* event)
{
	QPoint pos = event->angleDelta();
	if (pos.y()<0.)
	{
		MyCamera.Zoom += 1;
	}
	else
	{
		MyCamera.Zoom -= 1;
	}
	MyCamera.ProcessMouseScroll(pos.y());
}

void RenderWidget::InputProcess()
{
	if (FirstMouse)
	{
		LastX = MousePos.x;
		LastY = MousePos.y;
		FirstMouse = false;
	}
	float xOffset = MousePos.x - LastX;
	float yOffset = MousePos.y - LastY;
	LastX = MousePos.x;
	LastY = MousePos.y;
	MyCamera.ProcessMouseMovement(xOffset, yOffset);
}

RenderWidget::~RenderWidget()
{}
vector<vector3f>verts = 
{
	{-0.5f, -0.5f, -0.5f},{ 0.5f, -0.5f, -0.5f},{0.5f,  0.5f, -0.5f},{0.5f,  0.5f, -0.5f},{-0.5f,  0.5f, -0.5f},{-0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f, 0.5f },{ 0.5f, -0.5f, 0.5f },{0.5f,  0.5f,  0.5f},{0.5f,  0.5f,  0.5f},{-0.5f,  0.5f,  0.5f},{-0.5f, -0.5f,  0.5f},
	{-0.5f, 0.5f,  0.5f },{-0.5f, 0.5f,  -0.5f},{-0.5f,-0.5f, -0.5f},{-0.5f, -0.5f,-0.5f},{-0.5f,  -0.5f, 0.5f},{-0.5f, 0.5f,  0.5f},
	{ 0.5f, 0.5f,  0.5f },{0.5f,  0.5f,  -0.5f},{0.5f,  -0.5f,-0.5f},{0.5f,  -0.5f,-0.5f},{0.5f,  -0.5f,  0.5f},{0.5f, 0.5f,  0.5f},
	{-0.5f, -0.5f, -0.5f},{0.5f, -0.5f,  -0.5f},{0.5f,  -0.5f, 0.5f},{0.5f,  -0.5f, 0.5f},{-0.5f,  -0.5f, 0.5f},{-0.5f, -0.5f, -0.5f},
	{-0.5f, 0.5f, -0.5f },{0.5f, 0.5f,  -0.5f },{0.5f,  0.5f,  0.5f},{0.5f,  0.5f,  0.5f},{-0.5f,  0.5f,  0.5f},{-0.5f, 0.5f,  -0.5f}
};
vector<vector<int>>faces =
{
	{0,1,2},{3,4,5},
	{6,7,8},{9,10,11},
	{12,13,14},{15,16,17},
	{18,19,20},{21,22,23},
	{24,25,26},{27,28,29},
	{30,31,32},{33,34,35}	
};


vector<vector3f>normals =
{
	{ 0.0f,  0.0f, -1.0f},{ 0.0f,  0.0f, -1.0f},{ 0.0f,  0.0f, -1.0f},{ 0.0f,  0.0f, -1.0f},{ 0.0f,  0.0f, -1.0f},{ 0.0f,  0.0f, -1.0f},
	{ 0.0f,  0.0f,  1.0f},{ 0.0f,  0.0f,  1.0f},{ 0.0f,  0.0f,  1.0f},{ 0.0f,  0.0f,  1.0f},{ 0.0f,  0.0f,  1.0f},{ 0.0f,  0.0f,  1.0f},
	{-1.0f,  0.0f,  0.0f},{-1.0f,  0.0f,  0.0f},{-1.0f,  0.0f,  0.0f},{-1.0f,  0.0f,  0.0f},{-1.0f,  0.0f,  0.0f},{-1.0f,  0.0f,  0.0f},
	{ 1.0f,  0.0f,  0.0f},{ 1.0f,  0.0f,  0.0f},{ 1.0f,  0.0f,  0.0f},{ 1.0f,  0.0f,  0.0f},{ 1.0f,  0.0f,  0.0f},{ 1.0f,  0.0f,  0.0f},
	{ 0.0f, -1.0f,  0.0f},{ 0.0f, -1.0f,  0.0f},{ 0.0f, -1.0f,  0.0f},{ 0.0f, -1.0f,  0.0f},{ 0.0f, -1.0f,  0.0f},{ 0.0f, -1.0f,  0.0f},
	{ 0.0f,  1.0f,  0.0f},{ 0.0f,  1.0f,  0.0f},{ 0.0f,  1.0f,  0.0f},{ 0.0f,  1.0f,  0.0f},{ 0.0f,  1.0f,  0.0f},{ 0.0f,  1.0f,  0.0f}
};
vector<vector2f> uvs =
{
	{0.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},
	{1.0f, 1.0f},
	{0.0f, 1.0f},
	{0.0f, 0.0f},

	{0.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},
	{1.0f, 1.0f},
	{0.0f, 1.0f},
	{0.0f, 0.0f},

	{1.0f, 0.0f},
	{1.0f, 1.0f},
	{0.0f, 1.0f},
	{0.0f, 1.0f},
	{0.0f, 0.0f},
	{1.0f, 0.0f},

	{1.0f, 0.0f},
	{1.0f, 1.0f},
	{0.0f, 1.0f},
	{0.0f, 1.0f},
	{0.0f, 0.0f},
	{1.0f, 0.0f},

	{0.0f, 1.0f},
	{1.0f, 1.0f},
	{1.0f, 0.0f},
	{1.0f, 0.0f},
	{0.0f, 0.0f},
	{0.0f, 1.0f},

	{0.0f, 1.0f},
	{1.0f, 1.0f},
	{1.0f, 0.0f},
	{1.0f, 0.0f},
	{0.0f, 0.0f},
	{0.0f, 1.0f}
};


LoadModel* model = new LoadModel(verts, faces,uvs,normals);
LoadModel* model1 = new LoadModel("../Sourse/african_head.obj");

//main render
void RenderWidget::Render()
{
	int nowTime = QTime::currentTime().msecsSinceStartOfDay();
	if (CurrlastFrame!=0)
	{
		CurrdeltaTime = nowTime - CurrlastFrame;
		deltaTime = 1000.f / CurrdeltaTime;
	}
	CurrlastFrame = nowTime;
	InputProcess();
	ImageInstance::GetInstance().ClearImage();

	vsShader.view = MyCamera.GetViewMatrix();
	vsShader1.view = MyCamera.GetViewMatrix();
	vsShader2.view = MyCamera.GetViewMatrix();

	vsShader.projection = Perspective(MyCamera.Zoom, (float)Default_Width / (float)Default_Height, SCREEN_NEAR, SCREEN_FAR);
	vsShader1.projection = Perspective(MyCamera.Zoom, (float)Default_Width / (float)Default_Height, SCREEN_NEAR, SCREEN_FAR);
	vsShader2.projection = Perspective(MyCamera.Zoom, (float)Default_Width / (float)Default_Height, SCREEN_NEAR, SCREEN_FAR);


	ImageInstance::GetInstance().DrawModelWithFragment(model, vsShader,lfsShader);
	//ImageInstance::GetInstance().DrawModelWithFragment(model, vsShader1, pfsShader);
	//ImageInstance::GetInstance().DrawModelWithFragment(model, vsShader2, bfsShader);

	//ImageInstance::GetInstance().DrawWireframeModel(model1,vsShader);

	LightvsShader.view = MyCamera.GetViewMatrix();
	LightvsShader.projection = Perspective(MyCamera.Zoom, (float)Default_Width / (float)Default_Height, SCREEN_NEAR, SCREEN_FAR);


	ImageInstance::GetInstance().DrawModelWithFragment(model, LightvsShader, LightfsShader);
	
	ImageInstance::GetInstance().FillImage();
	ui.ImageBuffer->setPixmap(QPixmap::fromImage(ImageInstance::GetInstance().buffer.GetImage()));
	int t = ImageInstance::GetInstance().buffer.Frequency;
	



}


