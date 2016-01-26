<?php

/**
 * Add new domain page callback.
 */
function domain_black_list_add() {
  $domain = entity_create('domain_black_list', array('type' => DOMAIN_BLACK_LIST_BUNDLE));
  drupal_set_title(t('Create domain'));

  $output = drupal_get_form('domain_black_list_form', $domain);

  return $output;
}

/**
 * Domain add form.
 */
function domain_black_list_form($form, &$form_state, $domain) {
  $form_state['domain'] = $domain;

  // @todo validate
  $form['domain'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Domain'),
    '#maxlength' => 255,
    '#default_value' => $domain->domain,
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $domain->description,
  );

  $form['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Status'),
    '#default_value' => $domain->status,
  );

  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $domain->uid,
  );

  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array(
    '#weight' => 100,
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save domain'),
    '#submit' => $submit + array('domain_black_list_form_submit'),
  );

  // Show Delete button if we edit domain.
  $did = entity_id('domain_black_list' ,$domain);
  if (!empty($did) && domain_black_list_access('delete', $domain)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('domain_black_list_form_submit_delete'),
    );
  }

  $form['#validate'][] = 'domain_black_list_form_validate';

  return $form;
}

/**
 * Domain submit handler.
 */
function domain_black_list_form_submit($form, &$form_state) {
  $domain = $form_state['domain'];

  entity_form_submit_build_entity('domain_black_list', $domain, $form, $form_state);

  domain_black_list_save($domain);

  $form_state['redirect'] = DOMAIN_BLACK_LIST_ADMIN_PATH;

  drupal_set_message(t('Domain %title saved.', array('%title' => entity_label('domain_black_list', $domain))));
}

// @todo
function domain_black_list_form_validate($form, &$form_state) {

}


/**
 * Delete confirmation form.
 */
function domain_black_list_delete_form($form, &$form_state, $domain) {
  $form_state['domain'] = $domain;

  return confirm_form($form,
    t('Are you sure you want to delete domain %title?', array('%title' => entity_label('domain_black_list', $domain))),
    DOMAIN_BLACK_LIST_ADMIN_PATH,
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Delete form submit handler.
 */
function domain_black_list_delete_form_submit($form, &$form_state) {
  $domain = $form_state['domain'];
  domain_black_list_delete($domain);

  drupal_set_message(t('Domain %title deleted.', array('%title' => entity_label('domain_black_list', $domain))));

  $form_state['redirect'] = DOMAIN_BLACK_LIST_ADMIN_PATH;
}