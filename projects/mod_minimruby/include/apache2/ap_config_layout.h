/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file  ap_config_layout.h
 * @brief Apache Config Layout
 */

#ifndef AP_CONFIG_LAYOUT_H
#define AP_CONFIG_LAYOUT_H

/* Configured Apache directory layout */
#define DEFAULT_PREFIX ""
#define DEFAULT_EXP_EXEC_PREFIX "/usr"
#define DEFAULT_REL_EXEC_PREFIX "/usr"
#define DEFAULT_EXP_BINDIR "/usr/bin"
#define DEFAULT_REL_BINDIR "/usr/bin"
#define DEFAULT_EXP_SBINDIR "/usr/sbin"
#define DEFAULT_REL_SBINDIR "/usr/sbin"
#define DEFAULT_EXP_LIBEXECDIR "/usr/lib/apache2/modules"
#define DEFAULT_REL_LIBEXECDIR "/usr/lib/apache2/modules"
#define DEFAULT_EXP_MANDIR "/usr/share/man"
#define DEFAULT_REL_MANDIR "/usr/share/man"
#define DEFAULT_EXP_SYSCONFDIR "/etc/apache2"
#define DEFAULT_REL_SYSCONFDIR "/etc/apache2"
#define DEFAULT_EXP_DATADIR "/usr/share/apache2"
#define DEFAULT_REL_DATADIR "/usr/share/apache2"
#define DEFAULT_EXP_INSTALLBUILDDIR "/usr/share/apache2/build"
#define DEFAULT_REL_INSTALLBUILDDIR "/usr/share/apache2/build"
#define DEFAULT_EXP_ERRORDIR "/usr/share/apache2/error"
#define DEFAULT_REL_ERRORDIR "/usr/share/apache2/error"
#define DEFAULT_EXP_ICONSDIR "/usr/share/apache2/icons"
#define DEFAULT_REL_ICONSDIR "/usr/share/apache2/icons"
#define DEFAULT_EXP_HTDOCSDIR "/usr/share/apache2/default-site/htdocs"
#define DEFAULT_REL_HTDOCSDIR "/usr/share/apache2/default-site/htdocs"
#define DEFAULT_EXP_MANUALDIR "/usr/share/apache2/default-site/htdocs/manual"
#define DEFAULT_REL_MANUALDIR "/usr/share/apache2/default-site/htdocs/manual"
#define DEFAULT_EXP_CGIDIR "/usr/lib/cgi-bin"
#define DEFAULT_REL_CGIDIR "/usr/lib/cgi-bin"
#define DEFAULT_EXP_INCLUDEDIR "/usr/include/apache2"
#define DEFAULT_REL_INCLUDEDIR "/usr/include/apache2"
#define DEFAULT_EXP_LOCALSTATEDIR "/var/lock/apache2"
#define DEFAULT_REL_LOCALSTATEDIR "/var/lock/apache2"
#define DEFAULT_EXP_RUNTIMEDIR "/var/run/apache2"
#define DEFAULT_REL_RUNTIMEDIR "/var/run/apache2"
#define DEFAULT_EXP_LOGFILEDIR "/var/log/apache2"
#define DEFAULT_REL_LOGFILEDIR "/var/log/apache2"
#define DEFAULT_EXP_PROXYCACHEDIR "/var/cache/apache2/proxy"
#define DEFAULT_REL_PROXYCACHEDIR "/var/cache/apache2/proxy"
#define DEFAULT_PIDLOG "/var/run/apache2.pid"

#endif /* AP_CONFIG_LAYOUT_H */
