#ifndef ONGLETPLAYLIST_H
#define ONGLETPLAYLIST_H

#include <QWidget>

namespace Ui {
class OngletPlaylist;
}

class OngletPlaylist : public QWidget
{
    Q_OBJECT
    
public:
    explicit OngletPlaylist(QWidget *parent = 0);
    ~OngletPlaylist();
    
private:
    Ui::OngletPlaylist *ui;
};

#endif // ONGLETPLAYLIST_H
