#include	"page.hh"
#include    "IGUI.hh"

// ajouter ici le header de la page a ajouter
#include    "GeneralGUI.hh"
#include    "AccountGUI.hh"
#include    "SyncGUI.hh"
#include    "SignInGUI.hh"

// initialise les variables static
int Page::_idx = 0;

Page::Page(QWidget * parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->resize(522, 345);
    // ajouter une page a la suite, et respecter l'ordre de l'enum
    // sert a stocker les Pages dans un container
    _stack = new QStackedWidget;

    // sert pour le reload, mais ne jamais l'afficher
    _stack->addWidget(new QWidget());
    _stack->addWidget(new QWidget());
    _stack->addWidget(new GeneralGUI(_stack));
    _stack->addWidget(new AccountGUI(_stack));
    _stack->addWidget(new SyncGUI(_stack));
    _stack->addWidget(new SignInGUI(_stack));

    // appel la page correspondante a int (enum)
    connect(_stack, SIGNAL(currentChanged(int)), this, SLOT(update(int)));

    // initialise la classe a la page CONNECTION_PAGE
    update(Page::GENERAL_PAGE);
    _layout = new QVBoxLayout;
    _layout->addWidget(_stack);
    _layout->setMargin(0);
    setLayout(_layout);
    _stack->setCurrentIndex(Page::GENERAL_PAGE);
}

Page::~Page()
{
}

void	Page::update(int idx)
{
    // apres avoir changer le currentIndex de _stack, update la page pour l'afficher

    if (idx == Page::RELOAD_PAGE) {
        _stack->setCurrentIndex(_idx);
        return;
    } else if (idx == Page::DESTROY_PAGE) {
        delete this;
        return;
    }
    _idx = idx;
    // verifie si le widget existe bien
    IGUI * g = dynamic_cast<IGUI *>(_stack->widget(idx));

    if (g) {
      setBackground(idx);
      // appel la methode update de la page demande
      g->update();
    }
}

void	Page::setBackground(int idx) {
  switch (idx)
    {
    case Page::GENERAL_PAGE :
    case Page::ACCOUNT_PAGE :
    case Page::SYNC_PAGE :
    case Page::SIGNIN_PAGE :
      setBackgroundImage(":/fond");
      break;
    }
}

void	Page::setBackgroundImage(std::string str) {
  QPalette p = palette();
  QPixmap pixmap(str.c_str());
  pixmap = pixmap.scaled(this->size());

  p.setBrush(QPalette::Background, pixmap);
  setPalette(p);
}

void    Page::mousePressEvent(QMouseEvent * event) {
    _mpos = event->pos();
}

void    Page::mouseMoveEvent(QMouseEvent * event) {
    if (event->buttons() && Qt::LeftButton && _mpos.y() < HEIGHT_TITLE_BAR) {
        QPoint diff = event->pos() - _mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}
