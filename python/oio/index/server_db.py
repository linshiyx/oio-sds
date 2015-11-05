# Copyright (C) 2015 OpenIO, original work as part of
# OpenIO Software Defined Storage
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

import os
import time
import plyvel

from oio.common.utils import json


class IndexBackend(object):
    def __init__(self, conf):
        self.db_path = conf.get('db_path')
        self.dbs = {}
        if not os.path.exists(self.db_path):
            os.makedirs(self.db_path)

    def _get_db(self, volume):
        try:
            db = self.dbs[volume]
        except KeyError:
            self.dbs[volume] = plyvel.DB("%s/%s" % (self.db_path, volume), create_if_missing=True)
            db = self.dbs[volume]
        return db

    def put(self, volume, chunk_id, content_cid, content_path):
        #TODO replace content_path with content_id when available in git
        key = "%s|%s|%s" % (content_cid, content_path, chunk_id)
        value = json.dumps({"mtime": "%f" % time.time()})

        self._get_db(volume).put(str(key), str(value))

    def dump(self, volume):
        #TODO improve this method to use less memory
        data = dict()
        for key, value in self._get_db(volume):
            data[key] = value
        return data
