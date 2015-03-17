#include "salesmanweightmatrixmodel.h"
#include <QDebug>
#include <QBrush>
#include <QMimeData>
#include <QtMath>

void SalesmanWeightMatrixModel::resizeModel(int size)
{
    _size = size;
    _data.resize(_size * _size);
}

SalesmanWeightMatrixModel::SalesmanWeightMatrixModel(int size, QObject *parent) :
    QAbstractTableModel(parent)
{
    setSize(size);
}

int SalesmanWeightMatrixModel::rowCount(const QModelIndex &/*parent*/) const
{
    return _size;
}

int SalesmanWeightMatrixModel::columnCount(const QModelIndex &/*parent*/) const
{
    return _size;
}

QVariant SalesmanWeightMatrixModel::data(const QModelIndex &index, int role) const
{
    if(index.column() == index.row())
    {
        if(role == Qt::BackgroundRole)
            return QBrush(Qt::red);
        if(role == Qt::DisplayRole)
            return 0;
    }

    if(!index.isValid() || !(role == Qt::DisplayRole || role == Qt::EditRole))
        return QVariant();

    return _data.at(index.row() * _size + index.column());
}

QVariant SalesmanWeightMatrixModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    QString str = orientation == Qt::Horizontal ?
                trUtf8("В город") :
                trUtf8("Из города");

    return QString("%1 %2")
            .arg(str)
            .arg(QString::number(section + 1));
}

Qt::ItemFlags SalesmanWeightMatrixModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index) | Qt::ItemIsDropEnabled;
    if(index.isValid() && index.column() != index.row())
        return flags | Qt::ItemIsEditable;
    return flags;
}

std::vector<int> SalesmanWeightMatrixModel::getMatrixWeight() const
{
    return _data.toStdVector();
}

void SalesmanWeightMatrixModel::setSize(int size)
{
    beginResetModel();
    resizeModel(size);
    endResetModel();
    emit sizeChanged(size);
}

bool SalesmanWeightMatrixModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole || !index.isValid())
        return false;

    bool ok;
    int changedData = value.toInt(&ok);
    if(ok)
    {
        _data[index.row() * _size + index.column()] = changedData;
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::DropActions SalesmanWeightMatrixModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

bool SalesmanWeightMatrixModel::dropMimeData(const QMimeData *data,
                                             Qt::DropAction /*action*/,
                                             int /*row*/, int /*column*/,
                                             const QModelIndex &/*parent*/)
{    
    if(!data->hasText())
        return false;

    QString str = data->text();

    QTextStream out(&str, QIODevice::WriteOnly);

    QStringList stringsData = data->text().split(QRegExp("\\s"));
    QList<int> newData;
    foreach (QString str, stringsData)
    {
        bool ok;
        int val =str.toInt(&ok);
        if(ok)
            newData.push_back(val);
        else if(str == "∞")
            newData.push_back(0);
    }

    int newSize = qSqrt(newData.size());
    if(newSize * newSize != newData.size() ||
            newSize < 2)
        return false;

    beginResetModel();
    _size = newSize;
    _data = newData.toVector();
    endResetModel();
    emit sizeChanged(newSize);
    return true;
}

QStringList SalesmanWeightMatrixModel::mimeTypes() const
{
    return QAbstractTableModel::mimeTypes() << "text/plain";
}
