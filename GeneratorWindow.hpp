#ifndef GENERATORWINDOW_HPP
# define GENERATORWINDOW_HPP

# include <QMainWindow>
# include <QWidget>
# include <QtWidgets>
# include <QApplication>
# include <iostream>
# include <fstream>
# include <ctype.h>
# include <stdlib.h>
# include <sstream>

namespace Ui {
class GeneratorWindow;
}

class GeneratorWindow : public QWidget
{
    Q_OBJECT

    public:
        GeneratorWindow();
        GeneratorWindow(GeneratorWindow const & src);
        ~GeneratorWindow();
        GeneratorWindow & operator=(GeneratorWindow const & rhs);
        std::string             generateHPP(std::string);
        std::string             generateCPP(std::string);
        std::string             toUpperString(std::string str);
        bool                    isLowerCase(char c);
        int                     ft_strlen(char *str);
        void                    makeLayout(void);
    public slots:
        void             destinationAction(void);
        void             generateAction(void);
    private:
        QVBoxLayout      *layout;
        QLabel           *logo;
        QPushButton      *destination;
        QLabel           *path;
        std::string      pathString;
        QPushButton      *generate;
        QLineEdit        *className;

};

#endif // GENERATORWINDOW_HPP
