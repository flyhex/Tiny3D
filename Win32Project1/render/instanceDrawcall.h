/*
 * instanceDrawcall.h
 *
 *  Created on: 2017-9-29
 *      Author: a
 */

#ifndef INSTANCEDRAWCALL_H_
#define INSTANCEDRAWCALL_H_

class Instance;

#include "drawcall.h"

class InstanceDrawcall: public Drawcall {
private:
	int vertexCount,indexCount;
	bool indexed;
	Instance* instanceRef;
	RenderBuffer* dataBuffer2;

	RenderBuffer* dataBufferDraw;
	RenderBuffer* dataBufferPrepare;
	bool dynDC;
private:
	int objectToDraw;
public:
	int objectToPrepare;
	bool isSimple;
private:
	RenderBuffer* createBuffers(Instance* instance, bool dyn, bool indexed, int vertexCount, int indexCount);
public:
	InstanceDrawcall(Instance* instance);
	virtual ~InstanceDrawcall();
	virtual void draw(Shader* shader,int pass);
	void updateInstances(Instance* instance, int pass);
};

#endif /* INSTANCEDRAWCALL_H_ */
