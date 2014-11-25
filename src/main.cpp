//----------------------------------------------------------------------------
// The MIT License
// Took the basics from Polycode Examples
//----------------------------------------------------------------------------

#include "Polycode.h"
#include "PolycodeView.h"
#include "SyntheticsApp.hpp"

using namespace Synthetics;

int main(int argc, char *argv[]) {
	PolycodeView *view = new PolycodeView("Hello Polycode!");
	SyntheticsApp *app = new SyntheticsApp(view);
	while(app->Update()) {}
	return 0;
}
