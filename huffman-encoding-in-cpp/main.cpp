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
    catch (const std::exception &ex)
    {
    }

    return EXIT_SUCCESS;
}

class HuffmanNode
{
  public:
    char character;
    int frequency;
    HuffmanNode *left_ptr;
    HuffmanNode *right_ptr;
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
        throw std::runtime_error("Cannot encode text with length 0");
    }

    /* Create frequency map for each character */
    int frequency[256] = {0};
    for (char c : text_to_encode)
    {
        frequency[(int)c]++;
    }

    /* Create nodes and push them to min priority_queue */
    std::priority_queue<HuffmanNode *, struct huffman_node_compare> priority_q;
    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] > 0)
        {
            HuffmanNode *node = (HuffmanNode *)calloc(1, sizeof(HuffmanNode));
            node->character   = (char)i;
            node->frequency   = frequency[i];
            node->left_ptr    = NULL;
            node->right_ptr   = NULL;
            priority_q.push(node);
        }
    }
    free(frequency);

    /* Pop two nodes & merge them and do this until only the final merged node remains in the
     * priority queue */
    while (priority_q.size() > 1)
    {
        HuffmanNode *node1 = priority_q.top();
        priority_q.pop();
        HuffmanNode *node2 = priority_q.top();
        priority_q.pop();

        HuffmanNode *merged_node = (HuffmanNode *)calloc(1, sizeof(HuffmanNode));
        merged_node->character   = '\0';
        merged_node->frequency   = node1->frequency + node2->frequency;
        merged_node->left_ptr    = node1;
        merged_node->right_ptr   = node2;

        priority_q.push(merged_node);
    }

    /* Now, traverse this binare tree and keep appending a path to assign to leaf nodes */
    HuffmanNode *root = priority_q.top();
    std::vector<char> path(0);
    std::queue<std::pair<HuffmanNode *, char> *> node_q;
    std::pair<HuffmanNode *, char> *root_pair;
    root_pair->first  = root;
    root_pair->second = '\0';
    node_q.emplace(root_pair);
    while (node_q.size() > 0)
    {
        HuffmanNode *curr_node = node_q.front()->first;
        char encoding_char     = node_q.front()->second;
        node_q.pop();
        if (curr_node->left_ptr != nullptr)
        {
            std::pair<HuffmanNode *, char> *left_pair;
            left_pair->first  = curr_node->left_ptr;
            left_pair->second = '0';
            node_q.emplace(left_pair);
        }
        if (curr_node->right_ptr != nullptr)
        {
            std::pair<HuffmanNode *, char> *right_pair;
            right_pair->first  = curr_node->right_ptr;
            right_pair->second = '1';
            node_q.emplace(right_pair);
        }
        if (encoding_char != '\0')
        {
            path.push_back(encoding_char);
        }
    }
}
