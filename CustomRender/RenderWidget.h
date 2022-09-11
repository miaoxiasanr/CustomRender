#pragma once

#include <QWidget>
#include "ui_RenderWidget.h"
#include "ImageBuffer.h"
#include "QTimer"
#include <QTime>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include "qevent.h"
#include "CustomVector.h"
#include "CustomColor.h"
#include "CustomTexture.h"
#include "ImageInstance.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "LambertfsShader.h"
#include "Blinn_PhongfsShader.h"
#include "PhongfsShader.h"
#include "CustomMath.h"



class RenderWidget : public QWidget
{
	Q_OBJECT

public:
	RenderWidget(QWidget *parent = nullptr);
	~RenderWidget();
	void Render();

private:
	Ui::RenderWidgetClass ui;
	int Width;
	int Height;
	QTimer timer;
	Blinn_PhongfsShader* bfsShader;
	VertexShader vsShader;

	VertexShader vsShader1;
	VertexShader vsShader2;

	PhongfsShader* pfsShader;

	LambertfsShader* lfsShader;

	FragmentShader* LightfsShader;

	VertexShader LightvsShader;

protected:
	virtual void mouseMoveEvent(QMouseEvent* event) ;

	virtual void keyPressEvent(QKeyEvent* event);

	virtual void wheelEvent(QWheelEvent* event);

	void InputProcess();


};
