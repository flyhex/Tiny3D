#include "staticObject.h"
#include "../util/util.h"

StaticObject::StaticObject(Mesh* mesh) :Object() {
	this->mesh = mesh;
	this->meshMid = mesh;
	this->meshLow = mesh;
	anglex = 0; angley = 0; anglez = 0;

	transforms = (float*)malloc(4 * sizeof(float));
}

StaticObject::StaticObject(Mesh* mesh, Mesh* meshMid, Mesh* meshLow) :Object() {
	this->mesh = mesh;
	this->meshMid = meshMid;
	this->meshLow = meshLow;
	anglex = 0; angley = 0; anglez = 0;

	transforms = (float*)malloc(4 * sizeof(float));
}

StaticObject::StaticObject(const StaticObject& rhs) {
	mesh = rhs.mesh;
	meshMid = rhs.meshMid;
	meshLow = rhs.meshLow;
	material = rhs.material;
	if (rhs.bounding)
		bounding = rhs.bounding->clone();
	else
		bounding = NULL;
	anglex = rhs.anglex; angley = rhs.angley; anglez = rhs.anglez;

	position = rhs.position;
	sizex = rhs.sizex; sizey = rhs.sizey; sizez = rhs.sizez;
	localTransformMatrix = rhs.localTransformMatrix;
	normalMatrix = rhs.normalMatrix;
	localBoundPosition = rhs.localBoundPosition;

	genShadow = rhs.genShadow;
	detailLevel = rhs.detailLevel;

	if (rhs.billboard)
		setBillboard(rhs.billboard->data[0], rhs.billboard->data[1], rhs.billboard->material);
	if (rhs.transforms) {
		transforms = (float*)malloc(4 * sizeof(float));
		memcpy(transforms, rhs.transforms, 4 * sizeof(float));
	}
}

StaticObject::~StaticObject() {
	if (transforms) free(transforms);
	transforms = NULL;
}

StaticObject* StaticObject::clone() {
	return new StaticObject(*this);
}

void StaticObject::vertexTransform() {
	MATRIX4X4 translateMat=translate(position.x,position.y,position.z);
	MATRIX4X4 rotateMat=rotateZ(anglez)*rotateY(angley)*rotateX(anglex);
	MATRIX4X4 scaleMat = scale(sizex, sizey, sizez);
	localTransformMatrix=translateMat*rotateMat*scaleMat;
}

void StaticObject::normalTransform() {
	if(sizex==sizey&&sizey==sizez) {
		normalMatrix=localTransformMatrix;
		return;
	}
	normalMatrix=localTransformMatrix.GetInverse().GetTranspose();
}

void StaticObject::setPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
	updateLocalMatrices();
}

void StaticObject::setRotation(float ax, float ay, float az) {
	anglex = ax; angley = ay; anglez = az;
	updateLocalMatrices();
}

void StaticObject::setSize(float sx, float sy, float sz) {
	sizex = sx; sizey = sy; sizez = sz;
	updateLocalMatrices();
	if (billboard) {
		billboard->data[0] *= sizex;
		billboard->data[1] *= sizey;
	}
}





