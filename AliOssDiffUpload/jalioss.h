#ifndef JALIOSS_H
#define JALIOSS_H

#include <QObject>
class JAliOss : public QObject
{
    Q_OBJECT
public:
    explicit JAliOss(QObject *parent = nullptr);
    ~JAliOss();
    void SetCheckpointDir(const QString &path);
    //return error message
    QString DiffUpload(const QString &endpoint, const QString& key_id, const QString& key_secret,
                       const QString &bucket_name, const QString &object_name, const QString& local_path);
signals:

public slots:
private:
    QString _checkpoint_dir;
};

#endif // JALIOSS_H
