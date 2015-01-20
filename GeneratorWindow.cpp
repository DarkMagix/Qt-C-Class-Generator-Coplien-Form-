#include "GeneratorWindow.hpp"
#include "ui_GeneratorWindow.h"


GeneratorWindow::GeneratorWindow() : layout(new QVBoxLayout()), logo(new QLabel(this)), destination(new QPushButton("Destination", this)), path(new QLabel(this)), generate(new QPushButton("Generate", this))
{
    this->setWindowTitle("C++ Class Generator (Coplien Form)");
    this->makeLayout();
    QObject::connect(this->destination, SIGNAL(pressed()), this, SLOT(destinationAction()));
    QObject::connect(this->generate, SIGNAL(pressed()), this, SLOT(generateAction()));
}

GeneratorWindow::GeneratorWindow(GeneratorWindow const & src)
{
    *this = src;
}

GeneratorWindow::~GeneratorWindow()
{

}

GeneratorWindow &   GeneratorWindow::operator=(GeneratorWindow const & rhs){
    (void)rhs;
    return *this;
}

void        GeneratorWindow::makeLayout(void){
    this->setFixedSize(342, 442);
    QPixmap tmp("/Users/gmp/Documents/42/C++/Qt_projects/ClassGenerator/logo.png");
    QPixmap newPixmap = tmp.scaled(QSize(100,100),  Qt::KeepAspectRatio);
    this->logo->setPixmap(newPixmap);
    this->logo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QFormLayout *formLayout = new QFormLayout;

    this->layout->addWidget(this->logo);
    this->layout->addWidget(this->destination);
    this->layout->addWidget(this->path);
    this->layout->addLayout(formLayout);
    this->layout->addWidget(this->generate);

    this->className = new QLineEdit;
    formLayout->addRow("Class Name", className);

    this->setLayout(this->layout);
    this->path->setText("No destination folder chosen yet");
}

void        GeneratorWindow::destinationAction(){
    QString folder = QFileDialog::getExistingDirectory(this);
    this->pathString = folder.toStdString();
    this->path->setText(folder.toStdString().c_str());
}

void        GeneratorWindow::generateAction(void){
      try{
        if (this->pathString.compare("") == 0 || this->className->text().toStdString().compare("") == 0)
            throw std::exception();
        this->generateHPP(this->className->text().toStdString());
        this->generateCPP(this->className->text().toStdString());
      }
      catch(std::exception e){
            std::cout << e.what() << std::endl;
            QMessageBox::warning(this, "Empty path or class name", "Please give a path and a class name !");
      }
}

int                GeneratorWindow::ft_strlen(char *str){
    int     i = 0;
    while (str[i] != 0)
        i++;
    return i;
}

bool               GeneratorWindow::isLowerCase(char c){
    return ((c >= 'a' && c <= 'z') ? true : false);
}

std::string         GeneratorWindow::toUpperString(std::string str){
    char    *upper = (char *)malloc(sizeof(char) * ft_strlen((char *)str.c_str()) + 1);
    for (int i = 0; i < str.size(); i++){
        if (this->isLowerCase(static_cast<char>(str[i])))
            upper[i] = static_cast<char>(str[i]) - 32;
        else
            upper[i] = static_cast<char>(str[i]);
    }
    upper[str.size()] = 0;
    return static_cast<std::string>(upper);
}

std::string        GeneratorWindow::generateHPP(std::string name){
    std::stringstream ss;
                ss << "#ifndef " << this->toUpperString(name) << "_H" << std::endl;
                ss << "# define " << this->toUpperString(name) << "_H" << std::endl;

                ss << "class " << name << "{" << std::endl;
                ss << "public:" << std::endl;
                ss << "     " << name << "(void);" << std::endl;
                ss << "     " << name << "(" << name << " const & src);" << std::endl;
                ss << "     " << "~" << name << "(void);" << std::endl;
                ss << "     " << name << " & " << "operator=(" << name << " const & rhs);" << std::endl;

                ss << "};" << std::endl;
                ss << "#endif" << std::endl;

    std::string file = this->pathString + "/" + this->className->text().toStdString() + ".hpp";
    std::ofstream	hpp(file.c_str());
    hpp << ss.str();
    hpp.close();

    return ss.str();
}

std::string        GeneratorWindow::generateCPP(std::string name){
    std::stringstream ss;
        ss << "#include \"" << name << ".hpp\"" << std::endl << std::endl;
        ss << name << "::" << name << "(void){" << std::endl << std::endl << "}" << std::endl << std::endl;
        ss << name << "::" << name << "("  << name << " const & src){" << std::endl << std::endl;
        ss << "     *this = src;" << std::endl << "}" << std::endl << std::endl;
        ss << name << "::" << "~" << name << "(void){" << std::endl << std::endl << "}" << std::endl << std::endl;
        ss << name << " & " << name << "::" << "operator=(" << name << " const & rhs){" << std::endl;
        ss << "     (void)rhs;" << std::endl;
        ss << "     return *this;" << std::endl << "}" << std::endl;

    std::string file = this->pathString + "/" + this->className->text().toStdString() + ".cpp";
    std::ofstream	cpp(file.c_str());
    cpp << ss.str();
    cpp.close();
    return ss.str();
}
