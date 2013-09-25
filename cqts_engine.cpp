#include "cqts_engine.h"
#include <QFile>
#include <QTextStream>

CQTs_engine::CQTs_engine()
{
}

/*class handler*/
/*ClassFile structure:
 *Class Name
 *lv max
 *datanumber
 *endofile
 */
CQTs_Class::CQTs_Class(QString classLink){
    QFile file(classLink+".ClC");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&file);

            Name= in.readLine();
            in >> lmax;
            in >> data;

}
