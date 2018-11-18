

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>

struct passwd *pw = getpwuid(getuid());

const char *homedir = pw->pw_dir;
#include "miso_types.h"
#include "common.h"
#include "spinlock.h"
#include "timestamp.h"
#include "miso_log.h"


namespace UvoicInc {


static char s_UV_HOME[1024];
		

static void uv_check_create_dir(const char *dir) {
	struct stat st = {0};

	if (stat(dir, &st) == -1) {
	    mkdir(dir, 0755);
	}
}


static void uv_initailize() {
	
	char buf[1024], buf2[1024], buf3[1024];
	
	// initialize home dir
	struct passwd *pw = getpwuid(getuid());

	const char *homedir = pw->pw_dir;
	strcpy(s_UV_HOME, homedir);
	strcat(s_UV_HOME, "/.webkit-driver-uvc-inc");
	uv_check_create_dir(s_UV_HOME);
	
	// initialize log
	strcpy(buf, s_UV_HOME);
	strcat(buf, "/log");
	uv_check_create_dir(buf);
	
	::current_timestamp_str14(buf2, sizeof(buf2), mTRUE);
	snprintf(buf3, sizeof(buf3), "%s/wd_uvcinc_%s.log", buf, buf2);
	m_set_log_file(buf3);
	m_set_log_level(LOG_ALL);
	m_set_log_stdout(mTRUE);
	
	m_log_msg(LOG_INFO, "WebKit-Driver-Uvc-Inc initialization completed, with home dir [%s].",
				s_UV_HOME);
}

class UvoicInitializer {

public:
	UvoicInitializer() {
		uv_initailize();
	}
};

UvoicInitializer the_initializer;

} // namespace UvoicInc

