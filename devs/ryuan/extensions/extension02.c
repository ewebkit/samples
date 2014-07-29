/*
gcc -o libextension02.so extension02.c -fPIC -shared `pkg-config --cflags --libs ewebkit2-extension eina`

The example of extension which receives message from the ewebkit

TODO: It requires special ewebkit application.
*/

#include <stdio.h>
#include <Eina.h>
#include <EWebKit_Extension.h>

static void message_received(Ewk_Page *page, const char *name, const Eina_Value *value, void *data)
{
    fprintf(stderr, "%s is called\n", __func__);

    const Eina_Value_Type* type = eina_value_type_get(value);
    const char* string_value = NULL;
    if (type == EINA_VALUE_TYPE_STRING || type == EINA_VALUE_TYPE_STRINGSHARE)
        eina_value_get(value, &string_value);
    else
        string_value = "Not supported yet";

    fprintf(stderr, " > %s : (%s)\n", name, string_value);
}

void did_create_page(Ewk_Page *page, void *data)
{   
    fprintf(stderr, "%s is called\n", __func__);

    static Ewk_Page_Client client;
    client.message_received = message_received;

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

