/*
gcc -o libextension01.so extension01.c -fPIC -shared `pkg-config --cflags --libs ewebkit2-extension eina`

The example of extension which adds ryuan instance and hello method.

Usage: MiniBrowser -x /path/of/libextension01.so {below html}

<!doctype>
<body>
<input type="button" onclick="ryuan.hello();" value="click me">
</body>
*/

#include <stdio.h>
#include <Eina.h>
#include <EWebKit_Extension.h>
#include <JavaScriptCore/JavaScript.h>

static JSValueRef helloCallback(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    fprintf(stderr, "%s\n", __func__);
}

void load_finished(Ewk_Page* page, void *data)
{
    fprintf(stderr, "%s\n", __func__);

    JSGlobalContextRef jsContext = ewk_page_js_global_context_get(page);
    JSObjectRef windowObject = JSContextGetGlobalObject(jsContext);

    static JSStaticFunction functions[] = {
        { "hello", helloCallback, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete },
        { 0, 0, 0 }
    };
    static JSClassDefinition class_definition = {
        0, kJSClassAttributeNone, "Ryuan", 0, 0, functions,
        0, 0/* */, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    JSClassRef clasz = JSClassCreate(&class_definition);
    JSValueRef value = JSObjectMake(jsContext, clasz, data);
    JSClassRelease(clasz);

    JSValueRef exception = 0;
    JSStringRef property = JSStringCreateWithUTF8CString("ryuan");
    JSObjectSetProperty(jsContext, windowObject, property, value, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete, &exception);
    JSStringRelease(property);
}

void did_create_page(Ewk_Page *page, void *data)
{   
    fprintf(stderr, "%s is called\n", __func__);

    static Ewk_Page_Client client;
    client.load_finished = load_finished;

    ewk_page_client_add(page, &client);

}

void will_destroy_page(Ewk_Page *page, void *data)
{   
    fprintf(stderr, "%s is called\n", __func__);
}

void ewk_extension_init(Ewk_Extension *extension)
{   
    fprintf(stderr, "%s is called\n", __func__);
    
    static Ewk_Extension_Client client;
    client.did_Create_Page = did_create_page;
    client.will_Destroy_Page = will_destroy_page;
    
    ewk_extension_client_add(extension, &client);
}

