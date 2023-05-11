/*
 * 3. Реализуйте функции сериализации и десериализации двусвязного списка в бинарном формате в файл.
 * Алгоритмическая сложность решения должна быть меньше квадратичной. 
 */

#include <vector>
#include <unordered_map>
#include <string>

// структуру ListNode модифицировать нельзя
struct ListNode {
    ListNode * prev;
    ListNode * next;
    ListNode * rand; // указатель на произвольный элемент данного списка, либо NULL
    std::string data;
};

class List {
public:
    List()
    : head(nullptr)
    , tail(nullptr)
    , count(0)
    {}

    void Serialize (FILE * file); // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
    void Deserialize (FILE * file); // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

private:
    using NodesIds = std::unordered_map<ListNode * , size_t>;

    ListNode * head;
    ListNode * tail;
    int count;

    /**
     * @brief  Сериализует узел листа из файла.
     * @details Поле узла, отвечающее за случайный узел, будет сериализоваться как идентификатор
     * этого случайного узла.
     * @param file Файл, в который будет происходить сериализация.
     * @param node Узел, который будет сериализован.
     * @param randId Идентификатор случайного узла.
     */
    void SerializeListNode(FILE * file, ListNode * node, size_t randId) const;

    /**
     * @brief Десериализует узел листа из файла.
     * @param node Узел листа, в который будет произведена десериализация.
     * @param nodes Массив узлов листа.
     */
    void DeserializeListNode(FILE * file, ListNode * node) const;

    /**
     * @brief Создает хеш-таблицу сопоставляющую идентификатор узла к самому узлу.
     * @details Идентификатор начинается с 1.
     * @return хеш-таблицу: id -> node.
     */
    NodesIds makeNodesIds() const;
};

void List::Serialize(FILE *const file) {
    const NodesIds nodesIds = makeNodesIds();

    // будем считать что запись проходит без ошибок
    fwrite(&count, sizeof(int), 1u, file);
    for (ListNode * curNode = head; curNode != nullptr; curNode = curNode->next) {
        const size_t randId = (curNode->rand ? nodesIds.at(curNode->rand) : 0u);
        SerializeListNode(file, curNode, randId);
    }
}

void List::SerializeListNode(FILE *const file, ListNode *const node,
            const size_t randId) const {
    fwrite(&randId, sizeof(size_t), 1u, file);

    const size_t data_size = node->data.size();
    fwrite(&data_size, sizeof(size_t), 1u, file);

    for (const auto c : node->data) {
        fwrite(&c, sizeof(std::string::value_type), 1u, file);
    }
}

List::NodesIds List::makeNodesIds() const {
    NodesIds nodes;
    nodes.reserve(count);

    size_t id = 0u;
    for (ListNode * curNode = head; curNode != nullptr; curNode = curNode->next) {
        nodes[curNode] = ++id;
    }
    return nodes;
}

void List::Deserialize(FILE *const file) {
    std::unordered_map<size_t, ListNode *> idsToNodes;
    idsToNodes[0] = nullptr;

    fread(&count, sizeof(int), 1, file);
    const auto size = static_cast<size_t>(count);
    idsToNodes.reserve(size);
    std::vector<size_t> nodesRandIds;
    nodesRandIds.reserve(size);

    for (size_t i = 1u; i <= size; ++i) {
        idsToNodes[i] = new ListNode{};
        auto *const node = idsToNodes[i];

        size_t randId = 0u;
        fread(&randId, sizeof(size_t), 1u, file);
        nodesRandIds.push_back(randId);

        DeserializeListNode(file, node);

        auto *const prevNode = idsToNodes[i - 1u];
        if (prevNode) {
            prevNode->next = node;
        }
        node->prev = prevNode;
    }

    for (size_t i = 0u; i < size; ++i) {
        const size_t randId = nodesRandIds[i];
        idsToNodes[i + 1u]->rand = idsToNodes[randId];
    }

    head = idsToNodes[1u];
    tail = idsToNodes[size];
}

void List::DeserializeListNode(FILE *const file, ListNode *const node) const {
    size_t str_size = 0u;
    fread(&str_size, sizeof(size_t), 1u, file);
    for (size_t i = 0u; i < str_size; ++i) {
        std::string::value_type c = '\0';
        fread(&c, sizeof(std::string::value_type), 1u, file);
        node->data.push_back(c);
    }
}
