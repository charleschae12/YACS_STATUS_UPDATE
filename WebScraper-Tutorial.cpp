#include <iostream>
#include <fstream>
#include "scraper.h"

using namespace  std;

void WebTitle::StartElement(void *voidContext,
                         const xmlChar *name,
                         const xmlChar **attributes)
{
    auto *context = reinterpret_cast<Context*>(voidContext);

    if(attributes != nullptr && *attributes != nullptr)
    {
        if( (!context->dataExtracted) && !strcasecmp( context->tag.c_str() , reinterpret_cast<const char *>(name) ) &&
                !strcasecmp( *(reinterpret_cast<const char **>(attributes)), reinterpret_cast<const char *>(context->attr[0]))
                             && !strcasecmp( *(reinterpret_cast<const char **>(attributes)+1), reinterpret_cast<const char *>(context->attr[1]) ) )
        {
            context->title = "";
            context->addTitle = true;
        }
    }
}


//
//  libxml end element callback function
//

void WebTitle::EndElement(void *voidContext,
                       const xmlChar *name)
{
    auto *context = reinterpret_cast<Context*>(voidContext);

    if(!strcasecmp( reinterpret_cast<const char *>( name ), "div") && context->addTitle )
    {
         context->addTitle = false;
    }
}
