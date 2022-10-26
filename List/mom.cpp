template <class elm>
class MidMid
{
    void swap(elm const *n1, elm const *n2)
    {
        elm tmp = *n1;
        *n1 = *n2;
        *n2 = tmp;
    }
    //插入排序
    void sort(elm const *bg, elm const *ed)
    {
        for (elm *i = bg + 1; i != ed; ++i)
        {
            elm n = *i;
            for (elm *j = i; j > bg; --j)
            {
                elm tmp = *(j - 1);
                if (n < tmp)
                    *j = tmp;
                else
                    break;
            }
            *j = n;
        }
    }
    //取中置于开头
    elm const *median(elm const *bg, elm const *ed)
    {
        elm *loc = bg;
        elm *i;
        for (i = bg; i < ed - 4; i += 5)
        {
            sort(i, i + 5);
            *(loc++) = *(i + 2);
        }
        if (i < ed)
        {
            sort(i, ed);
            *(loc++) = *(i + (ed - i) / 2);
        }
    }
    //计算中值放开头
    void middle(elm const *bg, elm const *ed)
    {
        for (elm *i = ed; i != bg;)
            i = median(bg, i);
    }
    //划分
    void partition(elm const *bg, elm const *ed)
    {
    }
};