// addon.cc
#include <node.h>
#include <math.h>
#include "wrapper.h"
#include "typecastings.h"

namespace demo {

using namespace v8; 


void sgd(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  // Check the number of arguments passed.
  if (args.Length() < 6) {
    // Throw an Error that is passed back to JavaScript
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  // parse arguments
  Local<Array> xt = Local<Array>::Cast(args[0]);
  Local<Array> yt = Local<Array>::Cast(args[1]);
  
  unsigned int order = args[2]->NumberValue();
  double learning_rate = args[3]->NumberValue();
  unsigned int maxiter = args[4]->NumberValue();
  double minerr = args[5]->NumberValue();
  bool verbose = args[6]->BooleanValue();
  
  if (verbose)
  {
    printf("Verbose mode \n");
  }

  if (xt->Length() != yt->Length())
  {
    // Throw an Error that is passed back to JavaScript
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Input and Output lengths do not match.")));
    return;
  }

  // double* learned_slopes = learnSlope(xt, yt, order, learning_rate, maxiter, minerr, verbose);

  // export
  Local<Object> resp = wrapItUp(isolate, xt, yt, order, learning_rate, maxiter, minerr, verbose);

  // Set the return weight (using the passed in FunctionCallbackInfo<Value>&)
  args.GetReturnValue().Set(resp);
}


void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "sgd", sgd);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)

}  // namespace demo`