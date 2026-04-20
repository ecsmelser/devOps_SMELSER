#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

//test

void find_titles(xmlNode *node) {
    for (xmlNode *cur = node; cur != NULL; cur = cur->next) {
        if (cur->type == XML_ELEMENT_NODE &&
            xmlStrcmp(cur->name, (const xmlChar *)"title") == 0) {
            
            xmlChar *content = xmlNodeGetContent(cur);
            if (content != NULL) {
                printf("%s\n", content);
                xmlFree(content);
            }
        }

        find_titles(cur->children);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <xml_file>\n", argv[0]);
        return 1;
    }

    xmlDoc *doc = xmlReadFile(argv[1], NULL, 0);
    if (doc == NULL) {
        fprintf(stderr, "Error: could not parse file %s\n", argv[1]);
        return 1;
    }

    xmlNode *root = xmlDocGetRootElement(doc);
    if (root == NULL) {
        fprintf(stderr, "Error: empty XML document\n");
        xmlFreeDoc(doc);
        return 1;
    }

    printf("Book Titles:\n");
    find_titles(root);

    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 0;
}
