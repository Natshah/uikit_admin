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
 * Implements hook_css_alter().
 */
function uikit_admin_css_alter(&$css) {
  // Stop Drupal core stylesheets from being loaded.
  unset($css[drupal_get_path('module', 'system') . '/system.admin.css']);
}

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

/**
 * Implements hook_menu_local_tasks_alter().
 */
function uikit_admin_menu_local_tasks_alter(&$data, $router_item, $root_path) {
  // Define various icons.
  $plus = '<i class="uk-icon-plus"></i> ';

  foreach ($data['actions']['output'] as $key => $action) {
    preg_match('/(shortcut.*)\/add-link/', $action['#link']['path'], $matches);
    $shortcut_add_link = isset($matches[0]) && $matches[0] == 'shortcut/%/add-link';

    // Add icon for any shorcut add link path.
    if (isset($action['#link']['path']) && $shortcut_add_link) {
      $title = $plus . $data['actions']['output'][$key]['#link']['title'];
      $data['actions']['output'][$key]['#link']['title'] = $title;
      $data['actions']['output'][$key]['#link']['localized_options']['html'] = TRUE;
    }
  }
}
