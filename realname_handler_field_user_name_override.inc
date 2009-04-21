<?php
// $Id:

/**
 * Field handler for realnames
 */
class realname_handler_field_user_name_override extends views_handler_field_user_name {
  function init(&$view, &$data) {
    parent::init($view, $data);
    $this->additional_fields['uid'] = 'uid';
  }
  
  function render_link($data, $values) {
    $account = new stdClass();
    $account->uid = $values->{$this->aliases['uid']};
    $account->name = $values->{$this->field_alias};
    
    if (!empty($this->options['link_to_user']) || !empty($this->options['overwrite_anonymous'])) {
      if (!empty($this->options['overwrite_anonymous']) && !$account->uid) {
        // This is an anonymous user, and we're overriting the text.
        return check_plain($this->options['anonymous_text']);
      }
      elseif (!empty($this->options['link_to_user'])) {
        return theme('username', $account);
      }
    }
    // Otherwise, there's no special handling, so return the data directly.
    return realname_make_name($account);
  }

}
