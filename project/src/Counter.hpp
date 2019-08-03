#pragma once
#include <limits>

// ���ł��v������
template<class T> class Counter
{
#undef max
#undef min
private:
    T now_;     // ���݂̒l
    T add_;     // ���Z����l
    T min_;     // �ŏ��l
    T max_;     // �ő�l

public:
    // �R���X�g���N�^(���݂̒l��0�A���Z�ʂ�1)
    Counter():
        now_(0),
        add_(1),
        min_(std::numeric_limits<T>::min()),
        max_(std::numeric_limits<T>::max()) {}
    // �R���X�g���N�^(���Z�ʂ�ݒ�)
    Counter(T add):
        now_(0),
        add_(add),
        min_(std::numeric_limits<T>::min()),
        max_(std::numeric_limits<T>::max()) {}
    // �R���X�g���N�^(�ŏ��l�ƍő�l��ݒ�)
    Counter(T min, T max):
        now_(0),
        add_(1),
        min_(min),
        max_(max) {}
    // �R���X�g���N�^(���Z�ʂƍŏ��l�ƍő�l��ݒ�)
    Counter(T add, T min, T max):
        now_(0),
        add_(add),
        min_(min),
        max_(max) {}

    // �e���l��ݒ肷��
    void SetCounter(T setNow, T setAdd, T setMin, T setMax)
    {
        now_ = setNow;
        add_ = setAdd;
        min_ = setMin;
        max_ = setMax;
    }

    // ���݂̒l��0�ɂ���
    void Reset()
    {
        now_ = 0;
    }

    // ���݂̒l��ݒ肷��
    void SetNowCnt(T setNow)
    {
        now_ = setNow;
    }

    // ���݂̒l���ŏ��l�ɂ���
    void SetNowMin()
    {
        now_ = min_;
    }

    // ���݂̒l���ő�l�ɂ���
    void SetNowMax()
    {
        now_ = max_;
    }

    // ���l�����Z����
    // �ő�l�ȏ�A�ŏ��l�ȉ��ɂȂ�������Z���~����
    void Run()
    {
        now_ += add_;
        if (now_ <= min_) now_ = min_;
        if (now_ >= max_) now_ = max_;
    }

    // ���l�����Z����
    // �ő�l�𒴉߂�����ŏ��l�ɁA�ŏ��l�����ɂȂ�����ő�l�ɒ���
    void RunLoop()
    {
        now_ += add_;
        if (now_ < min_) now_ = max_;
        if (now_ > max_) now_ = min_;
    }

    // ���݂̒l��Ԃ�
    const T& GetNow() const
    {
        return now_;
    }

    // (�ő�l-���݂̒l)��Ԃ�
    T GetNowToMax() const
    {
        return max_ - now_;
    }

    // �ő�l��Ԃ�
    const T& GetMax() const
    {
        return max_;
    }

    // �ŏ��l��Ԃ�
    const T& GetMin() const
    {
        return min_;
    }

    // ���݂̒l���ő�l�܂œ��B���Ă�����true��Ԃ�
    bool IsMax() const
    {
        return now_ >= max_;
    }

    // ���݂̒l���ŏ��l�܂œ��B���Ă�����true��Ԃ�
    bool IsMin() const
    {
        return now_ <= min_;
    }
};