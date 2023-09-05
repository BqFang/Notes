#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* ����һ���ӿ� */
typedef struct ReadObjectPort {
	void (*DoOperation)(void *pvObject);
}REAL_OBJECT_PORT_T;

/* ������ʵ����ṹ�� */
typedef struct ReadObject {
	REAL_OBJECT_PORT_T tInterface;
}REAL_OBJECT_T;

/* �����������ṹ�� */
typedef struct Proxy {
	REAL_OBJECT_PORT_T tInterface;
	REAL_OBJECT_T tRealObject;
}PROXY_T;

/* ʵ����ʵ����Ĳ������� */
void RealOperation(void *pvObject)
{
	assert(pvObject);

	printf("opertion in RealObject\n\r");
}

/* ʵ�ִ������Ĳ������� */
void ProxyOperation(void *pvObject)
{
	assert(pvObject);
	PROXY_T *ptProxy = (PROXY_T *)pvObject;

	if (NULL == ptProxy)
	{
		return;
	}

	printf("operation in ProxyObject\n\r");

	ptProxy->tRealObject.tInterface.DoOperation = RealOperation;

	ptProxy->tRealObject.tInterface.DoOperation(ptProxy);
}

/* ����������� */
REAL_OBJECT_PORT_T* CreateProxy(void)
{
	PROXY_T *ptProxy = calloc(1, sizeof(PROXY_T));

	if (NULL == ptProxy)
	{
		return NULL;
	}

	ptProxy->tInterface.DoOperation = ProxyOperation;

	return &(ptProxy->tInterface);
}

/* ���ٴ������ */
void DestoryProxy(void *pvObject)
{
	assert(pvObject);

	REAL_OBJECT_PORT_T *ptProxy = (REAL_OBJECT_PORT_T *)pvObject;

	if (ptProxy)
	{
		free(ptProxy);
	}
}


int main()
{
	REAL_OBJECT_PORT_T *ptInterface = NULL;

	ptInterface = CreateProxy();

	ptInterface->DoOperation(ptInterface);

	DestoryProxy(ptInterface);

	return 0;
}

