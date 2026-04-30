#include <iostream>
#include <queue>
#include <string>

std::string huffman_encode(std::string text_to_encode);

int main()
{
    try
    {
        std::cout << "==HUFFMAN ENCODER==" << std::endl;

        std::cout << "Enter text to encode: ";
        std::string text_to_encode;
        std::getline(std::cin, text_to_encode);

        std::string encoded_text = huffman_encode(text_to_encode);
    }
    catch (const char *err)
    {
        std::cerr << err << std::endl;
    }

    return EXIT_SUCCESS;
}

class HuffmanNode
{
  public:
    char character;
    int frequency;
    HuffmanNode *leftPtr;
    HuffmanNode *rightPtr;
};

struct
{
    bool operator()(const HuffmanNode *left, const HuffmanNode *right) const
    {
        return left->frequency > right->frequency;
    }
} huffman_node_compare;

std::string huffman_encode(std::string text_to_encode)
{
    if (text_to_encode.length() == 0)
    {
        throw("Cannot encode text with length 0");
    }

    int frequency[256] = {0};
    for (char c : text_to_encode)
    {
        frequency[(int)c]++;
    }

    std::priority_queue<HuffmanNode *, struct huffman_node_compare> priority_q;
    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] > 0)
        {
            HuffmanNode *node = (HuffmanNode *)calloc(1, sizeof(HuffmanNode));
            node->character   = (char)i;
            node->frequency   = frequency[i];
            node->leftPtr     = NULL;
            node->rightPtr    = NULL;
            priority_q.push(node);
        }
    }
    free(frequency);

    while (priority_q.size() > 1)
    {
        HuffmanNode *node1 = priority_q.top();
        priority_q.pop();
        HuffmanNode *node2 = priority_q.top();
        priority_q.pop();

        HuffmanNode *merged_node = (HuffmanNode *)calloc(1, sizeof(HuffmanNode));
        merged_node->character   = '\0';
        merged_node->frequency   = node1->frequency + node2->frequency;
        merged_node->leftPtr     = node1;
        merged_node->rightPtr    = node2;

        priority_q.push(merged_node);
    }

    HuffmanNode *root = priority_q.top();
}
