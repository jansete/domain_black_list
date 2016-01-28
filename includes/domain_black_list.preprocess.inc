<?php

/**
 * Preprocess for example 1: Show message if feature is disabled.
 */
function template_preprocess_dbl_example_1(&$vars) {
  // @todo refactor
  if (!variable_get('domain_black_list_filter_html_page')) {
    drupal_set_message(t('This feature is disabled, go to !link', array(
      '!link' => l(t('settings form'), DOMAIN_BLACK_LIST_ADMIN_PATH . '/settings')))
    );
  }
}

/**
 * Preprocess for example 2: Show message if feature is disabled and prepare
 * links.
 */
function template_preprocess_dbl_example_2(&$vars) {
  // @todo refactor
  if (!variable_get('domain_black_list_alter_urls')) {
    drupal_set_message(t('This feature is disabled, go to !link', array(
      '!link' => l(t('settings form'), DOMAIN_BLACK_LIST_ADMIN_PATH . '/settings')))
    );
  }

  $vars['links'] = array(
    'http://google.es' => t('Google Spain'),
    'http://google.pl' => t('Google Poland'),
    'http://google.mx' => t('Google Mexico'),
  );
}