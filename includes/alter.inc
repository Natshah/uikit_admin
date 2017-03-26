<?php

/**
 * @file
 * Modify structured content arrays.
 *
 * These hooks are called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * content structure has been built.
 *
 * If the theme wishes to act on the rendered HTML of the content rather than
 * the structured content array, it may use this hook to add a #post_render
 * callback. Alternatively, it could also implement hook_preprocess_HOOK().
 *
 * @see drupal_render()
 * @see theme()
 */

/**
 * Implements hook_form_FORM_ID_alter() for filter_admin_format_form().
 */
function uikit_admin_form_filter_admin_format_form_alter(&$form, &$form_state) {
  $prefix = $form['filters']['status']['#prefix'];
  $form['filters']['status']['#prefix'] = str_replace('">', '" class="uk-form-row">', $prefix);
}

/**
 * Implements hook_form_FORM_ID_alter() for field_ui_display_overview_form().
 */
function uikit_admin_form_field_ui_display_overview_form_alter(&$form, &$form_state) {
  $form['fields']['#prefix'] = '';
  $form['fields']['#suffix'] = '';
}

/**
 * Implements hook_js_alter().
 */
function uikit_admin_js_alter(&$javascript) {
  $uikit_admin = drupal_get_path('theme', 'uikit_admin') . '/js';

  $block = drupal_get_path('module', 'block') . '/block.js';
  if (isset($javascript[$block])) {
    $javascript[$block]['data'] = $uikit_admin . '/block.js';
  }

  $dashboard = drupal_get_path('module', 'dashboard') . '/dashboard.js';
  if (isset($javascript[$dashboard])) {
    $javascript[$dashboard]['data'] = $uikit_admin . '/dashboard.js';
  }

  $tabledrag = 'misc/tabledrag.js';
  if (isset($javascript[$tabledrag])) {
    $javascript[$tabledrag]['data'] = $uikit_admin . '/tabledrag.js';
  }
}
