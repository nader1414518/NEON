#include <Neon.h>

class Sandbox : public Neon::Application {
public:
	Sandbox() {

	};

	~Sandbox() {

	};
};

Neon::Application* Neon::CreateApplication() {
	return new Sandbox();
};

//void main() {
//	/*Sandbox* sandbox = new Sandbox();
//	
//	sandbox->Run();
//
//	delete sandbox;*/
//}