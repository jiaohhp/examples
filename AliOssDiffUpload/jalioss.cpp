#include "jalioss.h"
#include <alibabacloud/oss/OssClient.h>
using namespace AlibabaCloud::OSS;
class JAliOssImpl
{
public:
    JAliOssImpl(const std::string &endpoint, const std::string &key_id, const std::string &key_secret);
    ~JAliOssImpl();
    //throw OssError
    PartList ListMultiparts(const std::string &bucket_name, const std::string &object_name, const std::string &upload_id);
    //throw OssError, return upload id
    std::string InitiateMultipartUpload(const std::string &bucket_name, const std::string &object_name);
    //throw OssError, return MD5
    std::string DoMultipartUpload(const std:string &bucket_name, const std::string &object_name, const std::string &upload_id,
                                  const std::shared_ptr<std::iostream>& content, int part_num, int length);
private:
    OssClient* _client;
};

JAliOssImpl::JAliOssImpl(const std::string &endpoint, const std::string &key_id, const std::string &key_secret)
{
    InitializeSdk();
    ClientConfiguration conf;
    _client = new OssClient(endpoint, key_id, key_secret, conf);
}

JAliOssImpl::~JAliOssImpl()
{
    delete _client;
    ShutdownSdk();
}

//throw OssError
PartList JAliOssImpl::ListMultiparts(const std::string &bucket_name, const std::string &object_name, const std::string &upload_id)
{
    PartList parts;
    /* 列举已上传分片，默认列举1000个分片 */
    ListPartsRequest listuploadrequest(bucket_name, object_name, upload_id);
    ListPartsOutcome listuploadresult;
    do {
        listuploadresult = _client->ListParts(listuploadrequest);
        if (!listuploadresult.isSuccess()) {
            throw listuploadresult.error();
        }
        else {
            parts.emplace_back(listuploadresult.result().PartList());
        }
        listuploadrequest.setPartNumberMarker(listuploadresult.result().NextPartNumberMarker());
    } while (listuploadresult.result().IsTruncated());

    return parts;
}

//throw OssError, return upload id
std::string JAliOssImpl::InitiateMultipartUpload(const std::string &bucket_name, const std::string &object_name)
{
    InitiateMultipartUploadRequest inituploadrequest(bucket_name, object_name);
    /*（可选）请参见如下示例设置存储类型 */
    //inituploadrequest.MetaData().addHeader("x-oss-storage-class", "Standard");

    /* 初始化分片上传事件 */
    InitiateMultipartUploadOutcome inituploadresult = _client->InitiateMultipartUpload(inituploadrequest);
    if(!inituploadresult.isSuccess()) throw inituploadresult.error();

    return inituploadresult.result().UploadId();
}

std::string JAliOssImpl::DoMultipartUpload(const std::string &bucket_name, const std::string &object_name, const std::string &upload_id,
                                    const std::shared_ptr<std::iostream>& content, int part_num, int length)
{
    UploadPartRequest uploadpartreuest(bucket_name, object_name, content);
    uploadpartreuest.setContentLength(length);
    uploadpartreuest.setUploadId(upload_id);
    uploadpartreuest.setPartNumber(part_num);
    PutObjectOutcome uploadpartresult = _client->UploadPart(uploadpartreuest);
    if (!uploadpartresult.isSuccess()) throw uploadpartresult.error();
    return uploadpartresult.result().ETag();
}
void JAliOss::SetCheckpointDir(const QString &path)
{
    _checkpoint_dir = path;
}

//return error message
QString JAliOss::DiffUpload(const QString &endpoint, const QString &key_id, const QString &key_secret,
                            const QString &bucket_name, const QString &object_name, const QString &local_path)
{
    JAliOssImpl impl(endpoint.toStdString(), key_id.toStdString(), key_secret.toStdString());
    try {
        std::string s_bucket_name = bucket_name.toStdString();
        std::string s_object_name = object_name.toStdString();
        std::string upload_id = impl.InitiateMultipartUpload(s_bucket_name, s_object_name);
        PartList uploaded_parts = impl.ListMultiparts(s_bucket_name, s_object_name, upload_id);

        /* skip valid uploaded parts */

    } catch (const OssError& err) {

    }
}
