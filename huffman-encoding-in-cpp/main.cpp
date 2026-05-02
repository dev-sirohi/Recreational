#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
#define NEWLINE "\r\n"
#else
#define NEWLINE "\n"
#endif

class HuffmanNode
{
  public:
    char character = '\0';
    int frequency  = 0;
    std::unique_ptr<HuffmanNode> left_ptr;
    std::unique_ptr<HuffmanNode> right_ptr;
};

struct HuffmanResult
{
    std::string data;
    std::string metadata;
};

/* API */
HuffmanResult huffman_encode(std::string text_to_encode);
std::string huffman_decode(const HuffmanResult &huffman_result);

/* MAIN */
int main()
{
    try
    {
        std::cout << "==HUFFMAN ENCODER/DECODER==" << std::endl;
        std::cout << "Note: Directly typed strings "
                     "cannot be decoded. Only files "
                     "with metadata support."
                  << std::endl;
        int user_input;
        std::cout << "Do you want to:-\n(1) Test the encoder, or\n(2) Encode a file, or\n(3) Decode a file?"
                  << std::endl;
        std::cout << "Enter: ";
        std::cin >> user_input;
        std::cin.ignore();

        switch (user_input)
        {
        case 1:
        {
            std::cout << "Enter text to encode: ";
            std::string text_to_encode;
            std::getline(std::cin, text_to_encode);

            const HuffmanResult huffman_result = huffman_encode(text_to_encode);
            std::cout << "Encoded text: ";
            std::cout << huffman_result.data << std::endl;
            break;
        }
        case 2:
        {
            std::cout << "Enter input filepath: " << std::endl;
            std::string input_file_path;
            std::cin >> input_file_path;
            std::cin.ignore();

            if (input_file_path.length() == 0)
            {
                throw std::runtime_error("Invalid file path");
            }

            std::ifstream input_file(input_file_path);
            std::string text_to_encode = "";
            std::getline(input_file, text_to_encode);

            std::cout << "Enter output filepath: " << std::endl;
            std::string output_file_path;
            std::cin >> output_file_path;
            std::cin.ignore();

            if (output_file_path.length() < 5)
            {
                throw std::runtime_error("Invalid file path");
            }
            if (output_file_path.substr(output_file_path.length() - 4, 4) != ".hfen")
            {
                throw std::runtime_error("Invalid file path. File type must be .hfen");
            }

            std::ofstream output_file(output_file_path);
            const HuffmanResult huffman_result = huffman_encode(text_to_encode);
            output_file << huffman_result.data;
            output_file << NEWLINE;
            output_file << huffman_result.metadata;
            break;
        }
        case 3:
        {
            std::cout << "Enter input filepath: " << std::endl;
            std::string input_file_path;
            std::cin >> input_file_path;
            std::cin.ignore();

            if (input_file_path.length() == 0)
            {
                throw std::runtime_error("Invalid file path");
            }
            if (input_file_path.substr(input_file_path.length() - 4, 4) != ".hfen")
            {
                throw std::runtime_error("Invalid file path. File type must be .hfen");
            }

            std::ifstream input_file(input_file_path);
            std::string text_to_encode = "";
            std::getline(input_file, text_to_encode);
            std::string metadata_text = "";
            for (std::string line; std::getline(input_file, line);)
            {
                metadata_text.append(line);
                metadata_text.append(NEWLINE);
            }
            input_file.close();

            std::cout << "Enter output filepath: " << std::endl;
            std::string output_file_path;
            std::cin >> output_file_path;
            std::cin.ignore();

            if (output_file_path.length() < 5)
            {
                throw std::runtime_error("Invalid file path");
            }

            std::ofstream output_file(output_file_path);
            output_file.clear();
            HuffmanResult huffman_result;
            huffman_result.data      = text_to_encode;
            huffman_result.metadata  = metadata_text;
            std::string decoded_text = huffman_decode(huffman_result);
            output_file << decoded_text;
            output_file.close();
            break;
        }
        case 4:
        {
            throw std::runtime_error("Wrong option");
        }
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    return EXIT_SUCCESS;
}

/* CORE */

class not_implemented_error : public std::runtime_error
{
  public:
    not_implemented_error() : std::runtime_error("Function not yet implemented")
    {
    }
};

static struct huffman_node_compare
{
    bool operator()(const std::unique_ptr<HuffmanNode> &left, const std::unique_ptr<HuffmanNode> &right) const
    {
        return left->frequency > right->frequency;
    }
};

static std::unique_ptr<HuffmanNode> get_huffman_tree_from_frequency_array(int *frequency)
{
    if (frequency == nullptr)
    {
        throw std::runtime_error("Invalid frequency array");
    }

    std::vector<std::unique_ptr<HuffmanNode>> heap;

    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] > 0)
        {
            auto node       = std::make_unique<HuffmanNode>();
            node->character = (char)i;
            node->frequency = frequency[i];
            node->left_ptr  = nullptr;
            node->right_ptr = nullptr;
            heap.push_back(std::move(node));
        }
    }

    std::make_heap(heap.begin(), heap.end(), huffman_node_compare());

    /* Pop two nodes & merge them and do this
     * until only the final merged node remains in
     * the priority queue */
    while (heap.size() > 1)
    {
        std::pop_heap(heap.begin(), heap.end(), huffman_node_compare());
        std::unique_ptr<HuffmanNode> node1 = std::move(heap.back());
        heap.pop_back();
        std::pop_heap(heap.begin(), heap.end(), huffman_node_compare());
        std::unique_ptr<HuffmanNode> node2 = std::move(heap.back());
        heap.pop_back();

        auto merged_node       = std::make_unique<HuffmanNode>();
        merged_node->character = '\0';
        merged_node->frequency = node1->frequency + node2->frequency;
        merged_node->left_ptr  = std::move(node1);
        merged_node->right_ptr = std::move(node2);

        heap.push_back(std::move(merged_node));
        std::push_heap(heap.begin(), heap.end(), huffman_node_compare());
    }

    auto root = std::move(heap.back());
    heap.pop_back();

    return root;
}

static void create_character_bitcode_map_from_huffman_tree(HuffmanNode *root,
                                                           std::unordered_map<int, std::string> &character_bitcode_map)
{
    std::queue<std::pair<const HuffmanNode *, std::string>> tree_traversal_queue;
    tree_traversal_queue.emplace(std::pair<const HuffmanNode *, std::string>(root, ""));
    while (!tree_traversal_queue.empty())
    {
        const HuffmanNode *merged_node = tree_traversal_queue.front().first;
        std::string path               = tree_traversal_queue.front().second;
        tree_traversal_queue.pop();

        if (merged_node->left_ptr == nullptr && merged_node->right_ptr == nullptr)
        {
            int c                    = (int)merged_node->character;
            character_bitcode_map[c] = path.empty() ? "0" : path;
            continue;
        }

        if (merged_node->left_ptr != nullptr)
        {
            tree_traversal_queue.emplace(
                std::pair<const HuffmanNode *, std::string>(merged_node->left_ptr.get(), path + "0"));
        }

        if (merged_node->right_ptr != nullptr)
        {
            tree_traversal_queue.emplace(
                std::pair<const HuffmanNode *, std::string>(merged_node->right_ptr.get(), path + "1"));
        }
    }
}

static void create_inverse_character_bitcode_map_from_huffman_tree(
    HuffmanNode *root, std::unordered_map<std::string, int> &inverse_character_bitcode_map)
{
    std::queue<std::pair<const HuffmanNode *, std::string>> tree_traversal_queue;
    tree_traversal_queue.emplace(std::pair<const HuffmanNode *, std::string>(root, ""));
    while (!tree_traversal_queue.empty())
    {
        const HuffmanNode *merged_node = tree_traversal_queue.front().first;
        std::string path               = tree_traversal_queue.front().second;
        tree_traversal_queue.pop();

        if (merged_node->left_ptr == nullptr && merged_node->right_ptr == nullptr)
        {
            int c                                                    = (int)merged_node->character;
            inverse_character_bitcode_map[path.empty() ? "0" : path] = c;
            continue;
        }

        if (merged_node->left_ptr != nullptr)
        {
            tree_traversal_queue.emplace(
                std::pair<const HuffmanNode *, std::string>(merged_node->left_ptr.get(), path + "0"));
        }

        if (merged_node->right_ptr != nullptr)
        {
            tree_traversal_queue.emplace(
                std::pair<const HuffmanNode *, std::string>(merged_node->right_ptr.get(), path + "1"));
        }
    }
}

HuffmanResult huffman_encode(std::string text_to_encode)
{
    if (text_to_encode.length() == 0)
    {
        throw std::runtime_error("Cannot encode text with length 0");
    }

    /* Create frequency map for each character */
    int frequency[256] = {0};
    for (char c : text_to_encode)
    {
        frequency[(int)((unsigned char)c)]++;
    }

    std::unique_ptr<HuffmanNode> root = get_huffman_tree_from_frequency_array(frequency);
    std::unordered_map<int, std::string> character_bitcode_map;
    create_character_bitcode_map_from_huffman_tree(root.get(), character_bitcode_map);

    std::string encoded_text = "";
    for (char c : text_to_encode)
    {
        if (!character_bitcode_map.contains(c))
        {
            throw std::runtime_error("Bad compression");
        }

        encoded_text.append(character_bitcode_map[c]);
    }
    std::string metadata = "";
    for (int f : frequency)
    {
        metadata.append(std::to_string(f));
        metadata.append(NEWLINE);
    }

    HuffmanResult huffman_result;
    huffman_result.data     = encoded_text;
    huffman_result.metadata = metadata;

    return huffman_result;
}

std::string huffman_decode(const HuffmanResult &huffman_result)
{
    const std::string &text_to_decode = huffman_result.data;
    if (text_to_decode.length() == 0)
    {
        throw std::runtime_error("Cannot decode text with length 0");
    }

    const std::string &metadata = huffman_result.metadata;
    if (metadata.length() == 0)
    {
        throw std::runtime_error("Cannot decode text without metadata");
    }

    // Metadata is numbers at ASCII codes separated by newlines
    int frequency[256];
    int f_index = 0;
    std::istringstream stream(metadata);
    for (std::string line; std::getline(stream, line, '\n');)
    {
        int string_length = line.length();
#ifdef _WIN32
        int offset = 2; // \r
#else
        int offset = 0;
#endif
        int freq           = std::stoi(line.substr(0, string_length - offset));
        frequency[f_index] = freq;
        f_index++;
    }

    if (f_index != 256)
    {
        throw std::runtime_error("Bad metadata. Invalid f_index end: " + std::to_string(f_index));
    }

    std::unique_ptr<HuffmanNode> root = get_huffman_tree_from_frequency_array(frequency);
    std::unordered_map<std::string, int> inverse_character_bitcode_map;
    create_inverse_character_bitcode_map_from_huffman_tree(root.get(), inverse_character_bitcode_map);

    std::string decoded_text = "";
    std::string bitcode      = "";
    for (char c : text_to_decode)
    {
        bitcode.push_back(c);
        if (inverse_character_bitcode_map.contains(bitcode))
        {
            decoded_text += inverse_character_bitcode_map[bitcode];
            bitcode.clear();
        }
    }

    if (!bitcode.empty())
    {
        throw std::runtime_error("Invalid encoded data");
    }

    return decoded_text;
}
