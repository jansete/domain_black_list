<?php

class DomainBlackList extends Entity {

  protected function defaultLabel() {
    return $this->domain;
  }

  public static function isDuplicated($domain_name, $domain_id = FALSE) {
    $query = db_select('domain_black_list', 'dbl');
    $query->fields('dbl', array('did'));
    $query->condition('dbl.domain', $domain_name);

    // Exclude current entity @see domain_black_list_form_validate
    if ($domain_id) {
      $query->condition('dbl.did', $domain_id, '<>');
    }

    $result = $query->execute();
    return $result->fetchField();
  }

  public static function isValid($domain_name, &$domain_filtered = NULL) {
    $not_clean_domain = $invalid_url = FALSE;
    $domain_pattern = '/^(?!\-)(?:[a-zA-Z\d\-]{0,62}[a-zA-Z\d]\.){1,126}(?!\d+)[a-zA-Z\d]{1,63}$/';

    if (!preg_match($domain_pattern, $domain_name)) {
      $not_clean_domain = TRUE;
      if ($host = parse_url($domain_name, PHP_URL_HOST)) {
        $domain_filtered = $host;
      }
      else {
        $invalid_url = TRUE;
      }
    }
    else {
      $domain_filtered = $domain_name;
    }

    return !$not_clean_domain && !$invalid_url || $not_clean_domain && !$invalid_url;
  }

  public static function getActives() {
    $query = db_select('domain_black_list', 'dbl');
    $query->fields('dbl', array('did','domain'));
    $query->condition('dbl.status', 1);
    $result = $query->execute();
    return $result->fetchAllKeyed();
  }
}