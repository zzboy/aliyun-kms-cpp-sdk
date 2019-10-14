#include <iostream>
#include "../utils.h"
#include "alibabacloud/core/AlibabaCloud.h"
#include "alibabacloud/kms/KmsClient.h"

using namespace std;
using namespace AlibabaCloud;
using namespace AlibabaCloud::Kms;

int main() {
  InitializeSdk();
  ClientConfiguration configuration("cn-hangzhou");
  Credentials credentials("STS.NKtAHEUZrjqvTNLmntMsVChRR", "GcXHL42hPTSw63AiXN1f6BeV3d8Hin6xnezKVGpND7Fx", "CAIS7QF1q6Ft5B2yfSjIr4jBCvLxuIVT3bOdVmj9iW4hQfx6rK35sDz2IHBOe3VhAOEcv/s3m25T6v4Ylq94T55IQ1CctkLZTCASo22beIPkl5Gfz95t0e+IewW6Dxr8w7WhAYHQR8/cffGAck3NkjQJr5LxaTSlWS7OU/TL8+kFCO4aRQ6ldzFLKc5LLw950q8gOGDWKOymP2yB4AOSLjIx5FMg0zIgsf3kk5DGsEKOtjCglL9J/baWC4O/csxhMK14V9qIx+FsfsLDqnUAsUcWpf4n1v0boWiZ5Y3FWUMx7xSAPObV9NJ/zdiz3RaR58UagAFFd7+xlJ99f0rpuy4TvKG1CuZCoDvXHS04QVoEDygr3OdGPA4LjcGUKnYUK0mZBpqLKm8oJVfD9l1GvWEvpzKbqxKs3H6yiV55IeXeQ6mNHZw+m391IwSp4YeGxPAz8czzOH5GNxws4tm9+HDZbgC0F9YT5ZWUBoQT17z0t+cWag==");
  KmsClient client(credentials, configuration);
  Model::DecryptRequest decryptRequest;
  decryptRequest.setEncryptionContext("{\"biz\":\"dingding\"}");
  decryptRequest.setCiphertextBlob("MjRjZTc5MmYtNzEwZC00YWU4LThhNGUtYTBmYjkxY2I0OTNkQXpqWDlEYzIxejFnSlZ6cFpnK1J0QWRHQzk4c1lGNmNBQUFBQUFBQUFBQldMUHZaTDlvalczWkwzbXMxczRRMGtCZGw5VUw1UFp1djM1RVhQa1BHTjkrR0czM2ZiN3k2");
  auto outcome = client.decrypt(request);
  cout << endl << "kms decrypt returned:" << endl;
  cout << "error code: " << outcome.error().errorCode() << endl;
  cout << "keyId: " << outcome.result().getKeyId() << endl << endl;
  cout << "plainText: " << outcome.result().getPlaintext() << endl << endl;
  cout << "KeyVersion: " << outcome.result().getKeyVersionId() << endl << endl;

  ShutdownSdk();
}
