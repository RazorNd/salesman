#ifndef SALESMANWEIGHTMATRIXMODEL_H
#define SALESMANWEIGHTMATRIXMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <vector>

class SalesmanWeightMatrixModel : public QAbstractTableModel
{
    Q_OBJECT
    int _size;
    QVector<int> _data;

    void resizeModel(int size);
public:
    explicit SalesmanWeightMatrixModel(int size, QObject *parent = 0);


    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    std::vector<int> getMatrixWeight() const;

signals:
    void sizeChanged(int size);

public slots:
    void setSize(int size);    

    Qt::DropActions supportedDropActions() const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    QStringList mimeTypes() const;
};

#endif // SALESMANWEIGHTMATRIXMODEL_H
