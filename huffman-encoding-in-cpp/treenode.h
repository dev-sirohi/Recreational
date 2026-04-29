#pragma once

template <typename T>
class TreeNode
{
private:
    T _value;
    TreeNode<T> *_leftPtr;
    TreeNode<T> *_rightPtr;

public:
    void set_value(T value)
    {
        _value = value;
    }

    void get_value()
    {
        return _value;
    }
};
