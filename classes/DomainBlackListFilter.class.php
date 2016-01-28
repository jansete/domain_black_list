<?php

class DomainBlackListFilter {

  /**
   * Format multiple domains to be a valid pattern for use in regular
   * expressions.
   */
  public static function formatDomains(&$domains, $pattern = 'html_link') {
    $result = array();
    $patterns = self::getPatterns();

    foreach ($domains as $domain) {
      $result[] = call_user_func_array($patterns[$pattern]['callback'], array($domain));
    }

    $domains = $result;
  }

  /**
   * List of patterns with them attributes.
   */
  public static function getPatterns() {
    return array(
      'html_link' => array(
        'callback' => 'DomainBlackListFilter::getHTMLLinkPattern',
      ),
      'simple_domain' => array(
        'callback' => 'DomainBlackListFilter::getSimpleDomainPattern',
      ),
      'valid_domain' => array(
        'callback' => 'DomainBlackListFilter::getValidDomainPattern',
      )
    );
  }

  /**
   * This pattern match with <a> HTML tag when has our domain as href HTML
   * attribute.
   */
  public static function getHTMLLinkPattern($domain) {
    return '/<a\s+(?:[^>]*?\s+)?href="http\:\/\/' . str_replace('.', '\\.', $domain) . '(.*?)"(.*?)>(.*?)<\/a>/im';
  }

  /**
   * This pattern match with the domain string.
   */
  public static function getSimpleDomainPattern($domain) {
    return $domain ? '/' . str_replace('.', '\\.', $domain) . '/i' : FALSE;
  }

  /**
   * This pattern validate a domain.
   */
  public static function getValidDomainPattern() {
    return '/^(?!\-)(?:[a-zA-Z\d\-]{0,62}[a-zA-Z\d]\.){1,126}(?!\d+)[a-zA-Z\d]{1,63}$/';
  }

  /**
   * Replace multiple domains patterns in a string with the $replace variable.
   */
  public static function replaceDomainsFromString($domains_patterns, &$string, $replace = '') {
    $count = 0;
    $string = preg_replace($domains_patterns, $replace, $string, -1, $count);

    return $count;
  }

  /**
   * Remove multiple domains patterns in a string.
   */
  public static function removeDomainsFromString($domains_patterns, &$string) {
    return self::replaceDomainsFromString($domains_patterns, $string);
  }

  /**
   * Get field types where validate it.
   * @todo create hook for extends with others modules
   * @todo add more fields types
   */
  public static function getValidateFieldTypesInfo() {
    return array(
      'text_long' => array(
        'properties_validation' => array('value')
      ),
      'text_with_summary' => array(
        'properties_validation' => array('value')
      ),
      // Requires link module
      'link_field' => array(
        'properties_validation' => array(
          'title',
          'url',
        ),
        'callback' => 'DomainBlackListFilter::linkFieldAlterFieldError'
      )
    );
  }

  public static function linkFieldAlterFieldError(&$error, $property) {
    $error['error_element']['url'] = $error['error_element']['title'] = FALSE;
    $error['error_element'][$property] = TRUE;
  }

  /**
   *  Get fields instances that belong in validate field types array in an
   *  entity.
   */
  public static function getValidateFieldsInstancesFromEntity($entity_type, $bundle) {
    $validate_fields_info = self::getValidateFieldTypesInfo();

    $query = db_select('field_config_instance', 'fci');
    $query->innerJoin('field_config', 'fc', 'fc.field_name = fci.field_name');
    $query->fields('fci', array('field_name'));
    $query->addField('fc', 'type');
    $query->condition('fci.entity_type', $entity_type)
      ->condition('fci.bundle', $bundle)
      ->condition('fc.type', array_keys($validate_fields_info), 'IN');
    return $query->execute()->fetchAll();
  }

  /**
   * If debug mode is enable, show debug information like a status message.
   */
  public static function showDebugMessage($message) {
    if (user_access(ADMINISTER_DOMAINS_BLACK_LIST_ENTITIES_PERM)) {
      drupal_set_message($message);
    }
  }

  /**
   * Show disable feature message, when access to a example page but this
   * feature is disabled.
   */
  public static function showDisableFeatureMessage() {
    self::showDebugMessage(t('This feature is disabled, go to !link', array(
        '!link' => l(t('settings form'), DOMAIN_BLACK_LIST_ADMIN_PATH . '/settings')))
    );
  }
}