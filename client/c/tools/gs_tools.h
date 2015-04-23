/*
OpenIO SDS client
Copyright (C) 2014 Worldine, original work as part of Redcurrant
Copyright (C) 2015 OpenIO, modified as part of OpenIO Software Defined Storage

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OIO_SDS__client__c__tools__gs_tools_h
# define OIO_SDS__client__c__tools__gs_tools_h 1

# include <metautils/lib/metautils.h>

#define ENV_CONTAINER "GS_CONTAINER"
#define ENV_META0URL "GS_META0URL"

#define DEFAULT_COMPRESSION_BLOCKSIZE 512000L

#define PRINT_DEBUG(FMT,...) \
do { if (flag_verbose) g_printerr("debug: "FMT, ##__VA_ARGS__); } while (0)

#define PRINT_ERROR(FMT,...) \
do { if (!flag_quiet) g_printerr("\nerror: "FMT, ##__VA_ARGS__); } while (0)

#define IGNORE_ARG(Arg) { if (!optarg) { PRINT_DEBUG("no argument given to the -%c parameter, ignoring it\r\n", Arg); break; } }

typedef struct s_gs_tools_options {
	char *meta0_url;
	char *container_name;
	char *user_metadata;
	GString *sys_metadata;
	int flag_help;
	int flag_force;
	int flag_verbose;
	int flag_quiet;
	int flag_info;
	int flag_cache;
	int flag_auto_create;
	int flag_full_chunks;
	int flag_activate_versioning;
	char *local_path;
	char *remote_path;
	char *base_dir;
	char *storage_policy;
	int offset;
	char *version;
	gint64 versioning;
	char *propkey;
	char *propvalue;
} t_gs_tools_options;

extern gchar* get_content_name(gchar *url);

extern gboolean is_content_specified(t_gs_tools_options *gto,
		gchar **extra_args);

extern gint gs_tools_main(int argc, gchar **argv, const gchar *cmd,
		void (*helpcb) (void));

extern gint gs_tools_main_with_argument_check(int argc, gchar **argv,
		const gchar *cmd, void (*helpcb) (void),
		gboolean (*check_args)(t_gs_tools_options*, gchar**));

#endif /*OIO_SDS__client__c__tools__gs_tools_h*/
