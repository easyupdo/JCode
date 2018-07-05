#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>
#include <QList>
//一个读音 有几个音标组成
typedef struct HM_PHONETIC
{
    QList<QString>hPhonetic;
}hmPhonetic,*HMPhonetic;
//一个单词有几个读音
typedef struct WORD_PHONETIC
{
    QList<hmPhonetic>wordAllPhonetic;

}wPhonetic,*WPhonetic;





#endif // GLOBAL_H
