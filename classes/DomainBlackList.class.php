<?php

class DomainBlackList extends Entity {

  /**
   * Return entity label.
   */
  protected function defaultLabel() {
    return $this->domain;
  }

  /**
   * Check if domain already exist.
   */
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

  /**
   * Check if domain has been written correctly.
   */
  public static function isValid($domain_name, &$domain_filtered = NULL) {
    $not_clean_domain = $invalid_url = FALSE;
    $domain_pattern = DomainBlackListFilter::getValidDomainPattern();

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

  /**
   * Get all actives domains ids.
   */
  public static function getActives() {
    $query = db_select('domain_black_list', 'dbl');
    $query->fields('dbl', array('did','domain'));
    $query->condition('dbl.status', 1);
    $result = $query->execute();
    return $result->fetchAllKeyed();
  }

  /**
   * Get all domains.
   */
  public static function getAll($pager = NULL, $limit = NULL, $start = 0) {

    if ($pager) {
      $query = db_select('domain_black_list', 'dbl')->extend('PagerDefault');
    }
    else {
      $query = db_select('domain_black_list', 'dbl');
    }

    if ($pager && $limit) {
      $query->limit($limit);
    }
    elseif ($limit) {
      $query->range($start, $limit);
    }

    return $query->fields('dbl', array('did','domain', 'status'))
      ->orderBy('dbl.did')
      ->execute();
  }

  /**
   *  Get some fake registers to test easier.
   */
  public static function getFakeDomains() {
    return array(
      array(
        'domain' => 'google.es',
        'description' => 'Spanish Google page.',
        'status' => 1,
        'uid' => 1,
      ),
      array(
        'domain' => 'marca.com',
        'description' => 'Sports news page.',
        'status' => 1,
        'uid' => 1,
      ),
      array(
        'domain' => 'drupal.org',
        'description' => 'Drupal website.',
        'status' => 1,
        'uid' => 1,
      ),
      array(
        'domain' => 'facebook.com',
        'description' => 'The big social network.',
        'status' => 0,
        'uid' => 1,
      ),
      array(
        'domain' => 'github.com',
        'description' => 'The main page for collaborate with the develop comunity.',
        'status' => 1,
        'uid' => 1,
      ),
      array(
        'domain' => 'youtube.com',
        'description' => 'Main video page.',
        'status' => 0,
        'uid' => 1,
      ),
      array(
        'domain' => 'hattrick.org',
        'description' => 'Online soccer manager game.',
        'status' => 0,
        'uid' => 1,
      ),
      array(
        'domain' => 'twitter.com',
        'description' => 'The social network with shortest messages.',
        'status' => 1,
        'uid' => 1,
      ),
      array(
        'domain' => 'platzi.com',
        'description' => 'Big community for learn developing.',
        'status' => 1,
        'uid' => 1,
      ),
      array(
        'domain' => 'gmail.com',
        'description' => 'The best free inbox email by Google.',
        'status' => 0,
        'uid' => 1,
      ),
      array(
        'domain' => 'linkedin.com',
        'description' => 'The business social network.',
        'status' => 1,
        'uid' => 1,
      ),
    );
  }
}