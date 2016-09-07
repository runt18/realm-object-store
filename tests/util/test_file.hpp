////////////////////////////////////////////////////////////////////////////
//
// Copyright 2016 Realm Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////

#ifndef REALM_TEST_UTIL_TEST_FILE_HPP
#define REALM_TEST_UTIL_TEST_FILE_HPP

#include "shared_realm.hpp"

#include <realm/version.hpp>
#if REALM_VER_MAJOR >= 2
#include <realm/history.hpp>
#else
#include <realm/commit_log.hpp>
#endif

struct TestFile : realm::Realm::Config {
    TestFile();
    ~TestFile();
};

struct InMemoryTestFile : TestFile {
    InMemoryTestFile();
};

void advance_and_notify(realm::Realm& realm);

static std::unique_ptr<realm::Replication> make_history(const std::string& path)
{
#if REALM_VER_MAJOR >= 2
    return realm::make_in_realm_history(path);
#else
    return realm::make_client_history(path);
#endif
}

#endif
