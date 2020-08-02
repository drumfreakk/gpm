#include "jsmn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * An example of how to access object members and array elements using jsmn.
 */

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

/* return next token, ignoring descendants */
jsmntok_t *skip_token(jsmntok_t *token)
{
	int pending = 1;
	do {
		pending += token->size - 1;
		token++;
	} while (pending);
	return token;
}

/* find the first member with the given name */
jsmntok_t *object_get_member(const char *json, jsmntok_t *object, const char *name)
{
	if (!object || object->type != JSMN_OBJECT || !name) {
		return NULL;
	}

	int members = object->size;
	jsmntok_t *token = object + 1;
	while (members && jsoneq(json, token, name) != 0) {
		members--;
		token = skip_token(token+1);
	}
	if (!members) {
		return NULL;
	}
	return token + 1;
}

/* find the element at the given position of an array (starting at 0). */
jsmntok_t *array_get_at(jsmntok_t *object, int index)
{
	if (!object || object->type != JSMN_ARRAY || index < 0 
	|| object->size <= index) {
		return NULL;
	}

	jsmntok_t *token = object + 1;
	for (int i = 0; i < index; i++) {
		token = skip_token(token);
	}
	return token;
}

/* type to string */
const char *jsmntype_str(jsmntype_t type)
{
	switch(type) {
	case JSMN_UNDEFINED: return "UNDEFINED";
	case JSMN_OBJECT: return "OBJECT";
	case JSMN_ARRAY: return "ARRAY";
	case JSMN_STRING: return "STRING";
	case JSMN_PRIMITIVE: return "PRIMITIVE";
	}
}

/*
{
	"a": 1,
	"b": {
		"c": [{"d": 2}, {"d": 3}]
	}
}
*/

static const char *JSON_TEXT = "[{\"url\":\"https://api.github.com/repos/kippenjongen/gpm-test-repo/releases/29191377\",\"assets_url\":\"https://api.github.com/repos/kippenjongen/gpm-test-repo/releases/29191377/assets\",\"upload_url\":\"https://uploads.github.com/repos/kippenjongen/gpm-test-repo/releases/29191377/assets{?name,label}\",\"html_url\":\"https://github.com/kippenjongen/gpm-test-repo/releases/tag/v2.0\",\"id\":29191377,\"node_id\":\"MDc6UmVsZWFzZTI5MTkxMzc3\",\"tag_name\":\"v2.0\",\"target_commitish\":\"master\",\"name\":\"with assets\",\"draft\":false,\"author\":{\"login\":\"kippenjongen\",\"id\":23664790,\"node_id\":\"MDQ6VXNlcjIzNjY0Nzkw\",\"avatar_url\":\"https://avatars3.githubusercontent.com/u/23664790?v=4\",\"gravatar_id\":\"\",\"url\":\"https://api.github.com/users/kippenjongen\",\"html_url\":\"https://github.com/kippenjongen\",\"followers_url\":\"https://api.github.com/users/kippenjongen/followers\",\"following_url\":\"https://api.github.com/users/kippenjongen/following{/other_user}\",\"gists_url\":\"https://api.github.com/users/kippenjongen/gists{/gist_id}\",\"starred_url\":\"https://api.github.com/users/kippenjongen/starred{/owner}{/repo}\",\"subscriptions_url\":\"https://api.github.com/users/kippenjongen/subscriptions\",\"organizations_url\":\"https://api.github.com/users/kippenjongen/orgs\",\"repos_url\":\"https://api.github.com/users/kippenjongen/repos\",\"events_url\":\"https://api.github.com/users/kippenjongen/events{/privacy}\",\"received_events_url\":\"https://api.github.com/users/kippenjongen/received_events\",\"type\":\"User\",\"site_admin\":false},\"prerelease\":false,\"created_at\":\"2020-08-01T12:04:01Z\",\"published_at\":\"2020-08-01T12:07:04Z\",\"assets\":[{\"url\":\"https://api.github.com/repos/kippenjongen/gpm-test-repo/releases/assets/23493051\",\"id\":23493051,\"node_id\":\"MDEyOlJlbGVhc2VBc3NldDIzNDkzMDUx\",\"name\":\"bot.py\",\"label\":null,\"uploader\":{\"login\":\"kippenjongen\",\"id\":23664790,\"node_id\":\"MDQ6VXNlcjIzNjY0Nzkw\",\"avatar_url\":\"https://avatars3.githubusercontent.com/u/23664790?v=4\",\"gravatar_id\":\"\",\"url\":\"https://api.github.com/users/kippenjongen\",\"html_url\":\"https://github.com/kippenjongen\",\"followers_url\":\"https://api.github.com/users/kippenjongen/followers\",\"following_url\":\"https://api.github.com/users/kippenjongen/following{/other_user}\",\"gists_url\":\"https://api.github.com/users/kippenjongen/gists{/gist_id}\",\"starred_url\":\"https://api.github.com/users/kippenjongen/starred{/owner}{/repo}\",\"subscriptions_url\":\"https://api.github.com/users/kippenjongen/subscriptions\",\"organizations_url\":\"https://api.github.com/users/kippenjongen/orgs\",\"repos_url\":\"https://api.github.com/users/kippenjongen/repos\",\"events_url\":\"https://api.github.com/users/kippenjongen/events{/privacy}\",\"received_events_url\":\"https://api.github.com/users/kippenjongen/received_events\",\"type\":\"User\",\"site_admin\":false},\"content_type\":\"text/x-python\",\"state\":\"uploaded\",\"size\":364,\"download_count\":1,\"created_at\":\"2020-08-01T12:07:00Z\",\"updated_at\":\"2020-08-01T12:07:00Z\",\"browser_download_url\":\"https://github.com/kippenjongen/gpm-test-repo/releases/download/v2.0/bot.py\"}],\"tarball_url\":\"https://api.github.com/repos/kippenjongen/gpm-test-repo/tarball/v2.0\",\"zipball_url\":\"https://api.github.com/repos/kippenjongen/gpm-test-repo/zipball/v2.0\",\"body\":\"\"},{\"url\":\"https://api.github.com/repos/kippenjongen/gpm-test-repo/releases/29191352\",\"assets_url\":\"https://api.github.com/repos/kippenjongen/gpm-test-repo/releases/29191352/assets\",\"upload_url\":\"https://uploads.github.com/repos/kippenjongen/gpm-test-repo/releases/29191352/assets{?name,label}\",\"html_url\":\"https://github.com/kippenjongen/gpm-test-repo/releases/tag/v1.1\",\"id\":29191352,\"node_id\":\"MDc6UmVsZWFzZTI5MTkxMzUy\",\"tag_name\":\"v1.1\",\"target_commitish\":\"master\",\"name\":\"second release\",\"draft\":false,\"author\":{\"login\":\"kippenjongen\",\"id\":23664790,\"node_id\":\"MDQ6VXNlcjIzNjY0Nzkw\",\"avatar_url\":\"https://avatars3.githubusercontent.com/u/23664790?v=4\",\"gravatar_id\":\"\",\"url\":\"https://api.github.com/users/kippenjongen\",\"html_url\":\"https://github.com/kippenjongen\",\"followers_url\":\"https://api.github.com/users/kippenjongen/followers\",\"following_url\":\"https://api.github.com/users/kippenjongen/following{/other_user}\",\"gists_url\":\"https://api.github.com/users/kippenjongen/gists{/gist_id}\",\"starred_url\":\"https://api.github.com/users/kippenjongen/starred{/owner}{/repo}\",\"subscriptions_url\":\"https://api.github.com/users/kippenjongen/subscriptions\",\"organizations_url\":\"https://api.github.com/users/kippenjongen/orgs\",\"repos_url\":\"https://api.github.com/users/kippenjongen/repos\",\"events_url\":\"https://api.github.com/users/kippenjongen/events{/privacy}\",\"received_events_url\":\"https://api.github.com/users/kippenjongen/received_events\",\"type\":\"User\",\"site_admin\":false},\"prerelease\":false,\"created_at\":\"2020-08-01T12:04:01Z\",\"published_at\":\"2020-08-01T12:04:42Z\",\"assets\":[],\"tarball_url\":\"https://api.github.com/repos/kippenjongen/gpm-test-repo/tarball/v1.1\",\"zipball_url\":\"https://api.github.com/repos/kippenjongen/gpm-test-repo/zipball/v1.1\",\"body\":\"\"},{\"url\":\"https://api.github.com/repos/kippenjongen/gpm-test-repo/releases/29191260\",\"assets_url\":\"https://api.github.com/repos/kippenjongen/gpm-test-repo/releases/29191260/assets\",\"upload_url\":\"https://uploads.github.com/repos/kippenjongen/gpm-test-repo/releases/29191260/assets{?name,label}\",\"html_url\":\"https://github.com/kippenjongen/gpm-test-repo/releases/tag/v1.0\",\"id\":29191260,\"node_id\":\"MDc6UmVsZWFzZTI5MTkxMjYw\",\"tag_name\":\"v1.0\",\"target_commitish\":\"master\",\"name\":\"test\",\"draft\":false,\"author\":{\"login\":\"kippenjongen\",\"id\":23664790,\"node_id\":\"MDQ6VXNlcjIzNjY0Nzkw\",\"avatar_url\":\"https://avatars3.githubusercontent.com/u/23664790?v=4\",\"gravatar_id\":\"\",\"url\":\"https://api.github.com/users/kippenjongen\",\"html_url\":\"https://github.com/kippenjongen\",\"followers_url\":\"https://api.github.com/users/kippenjongen/followers\",\"following_url\":\"https://api.github.com/users/kippenjongen/following{/other_user}\",\"gists_url\":\"https://api.github.com/users/kippenjongen/gists{/gist_id}\",\"starred_url\":\"https://api.github.com/users/kippenjongen/starred{/owner}{/repo}\",\"subscriptions_url\":\"https://api.github.com/users/kippenjongen/subscriptions\",\"organizations_url\":\"https://api.github.com/users/kippenjongen/orgs\",\"repos_url\":\"https://api.github.com/users/kippenjongen/repos\",\"events_url\":\"https://api.github.com/users/kippenjongen/events{/privacy}\",\"received_events_url\":\"https://api.github.com/users/kippenjongen/received_events\",\"type\":\"User\",\"site_admin\":false},\"prerelease\":false,\"created_at\":\"2020-08-01T11:54:05Z\",\"published_at\":\"2020-08-01T11:54:26Z\",\"assets\":[],\"tarball_url\":\"https://api.github.com/repos/kippenjongen/gpm-test-repo/tarball/v1.0\",\"zipball_url\":\"https://api.github.com/repos/kippenjongen/gpm-test-repo/zipball/v1.0\",\"body\":\"\"}]";

#define MAX_TOKENS 500

int main(void)
{
	jsmn_parser jsmn;
	jsmn_init(&jsmn);
	jsmntok_t tokens[MAX_TOKENS];

	int n = jsmn_parse(&jsmn, JSON_TEXT, strlen(JSON_TEXT), tokens, MAX_TOKENS);	
	if (n < 0) {
		printf("Parse error: %d\n", n);
		return 1;
	}

	/* print the token list for reference */	
	for (int i = 0; i < n; i++) {
		jsmntok_t *t = &tokens[i];
		printf("%d %.*s type:%s start:%d end:%d size %d\n", i, t->end - t->start
			, JSON_TEXT + t->start, jsmntype_str(t->type), t->start, t->end
			, t->size); 
	}
	printf("\n");

	/* locate the elements of the json and print their locations */
	jsmntok_t *root = &tokens[0];
	jsmntok_t *a = object_get_member(JSON_TEXT, root, "url");
	printf("a is token %d\n", a - root);
	jsmntok_t *b = object_get_member(JSON_TEXT, root, "b");
	printf("b is token %d\n", b - root);
	jsmntok_t *x = object_get_member(JSON_TEXT, root, "x");
	printf("x found: %s\n", x ? "yes" : "no");
	jsmntok_t *c = object_get_member(JSON_TEXT, b, "c");
	printf("c is token %d\n", c - root);
	jsmntok_t *t = array_get_at(c, 0);
	printf("c[0] is token %d\n", t - root);
	t = array_get_at(c, 1);
	printf("c[1] is token %d\n", t - root);
	t = array_get_at(c, 2);
	printf("c[2] found: %s\n", t ? "yes" : "no");

	return 0;
}
