#include <libxml/tree.h>
#include <iostream>

using namespace std;

static void print_elements(xmlNode *node) {
    xmlNode *cur_node = NULL;

    for (cur_node = node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            cout << "Node type: Element, Name: \"" << cur_node->name << "\"";

            std::string elem = (char *) cur_node->name;
            char* tmp;
            if (elem == "dirs" && (tmp = (char *)xmlNodeGetContent(cur_node)))
            {
                // xmlTextMerge(*value, cur_node);
                int len = strlen(tmp);
                cout << ", Value: \"" << tmp << "\", Length: " << len << endl;
            } else {
                cout << endl;
            }
        }

        print_elements(cur_node->children);
    }
}

int main(void) {
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    LIBXML_TEST_VERSION

    doc = xmlReadFile("/Users/gkrishna/Desktop/personalws/cpp/xmlparser/src/xml/config.xml", NULL, 0);

    if (doc == NULL) {
        cout << "Error: could not parse file \"xml/config.xml\"" << endl;
        return -1;
    }

    root_element = xmlDocGetRootElement(doc);
    print_elements(root_element);

    xmlFreeDoc(doc);

    // xmlCleanupParser();

    return 0;
}