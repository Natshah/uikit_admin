<?php

/**
 * @file
 * The theme system, which controls the output of the UIkit Admin theme.
 */

/**
 * Implements theme_admin_block().
 */
function uikit_admin_admin_block($variables) {
  $block = $variables['block'];
  $output = '';

  // Don't display the block if it has no content to display.
  if (empty($block['show'])) {
    return $output;
  }

  $output .= '<div class="uk-panel uk-panel-box uk-panel-header uk-margin-bottom">';

  if (!empty($block['title'])) {
    $output .= '<h3 class="uk-panel-title uk-text-bold uk-text-uppercase">' . $block['title'] . '</h3>';
  }

  if (!empty($block['content'])) {
    $output .= '<div class="body">' . $block['content'] . '</div>';
  }
  else {
    $output .= '<div class="description">' . $block['description'] . '</div>';
  }

  $output .= '</div>';

  return $output;
}

/**
 * Implements theme_admin_block_content().
 */
function uikit_admin_admin_block_content($variables) {
  $content = $variables['content'];
  $output = '';

  if (!empty($content)) {
    $classes = 'uk-list uk-list-line uk-margin-remove uk-admin-list';

    if (system_admin_compact_mode()) {
      $classes .= ' uk-admin-list-compact';
    }

    $output .= '<ul class="' . $classes . '">';

    foreach ($content as $item) {
      $item['localized_options']['attributes']['class'][] = 'uk-text-bold';
      $output .= '<li>';

      if (!system_admin_compact_mode()) {
        $output .= '<i class="uk-icon-chevron-circle-right uk-text-muted uk-display-inline-block uk-admin-vertical-align-top" style="margin-top: 2px"></i>';
        $output .= '<div class="uk-margin-left uk-display-inline-block">';
        $output .= l($item['title'], $item['href'], $item['localized_options']);
      }
      else {
        $output .= l($item['title'], $item['href'], $item['localized_options']);
      }

      if (isset($item['description']) && !system_admin_compact_mode()) {
        $output .= '<div class="uk-text-muted">' . filter_xss_admin($item['description']) . '</div>';
      }

      if (!system_admin_compact_mode()) {
        $output .= '</div>';
      }

      $output .= '</li>';
    }

    $output .= '</ul>';
  }
  return $output;
}

/**
 * Implements theme_breadcrumb().
 */
function uikit_admin_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  $output = '';

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .uk-hidden.
    $output .= '<h2 class="uk-hidden">' . t('You are here') . '</h2>';

    $output .= '<ul class="uk-breadcrumb">';

    foreach ($breadcrumb as $crumb) {
      $output .= '<li>' . $crumb . '</li>';
    }

    $output .= '</ul>';
  }

  return $output;
}

/**
 * Implements theme_fieldset().
 */
function uikit_admin_fieldset($variables) {
  $element = $variables['element'];
  $collapsed = $element['#collapsed'];
  element_set_attributes($element, array('id'));
  _form_set_class($element, array('uk-panel', 'uk-panel-box', 'form-wrapper'));
  $id = $element['#attributes']['id'];

  // When viewing the theme settings page for a specific theme, add the
  // .uk-admin-panel-box-light class to theme nested fieldsets.
  if (substr(current_path(), 0, 26) === 'admin/appearance/settings/') {
    $theme_key = arg(3);
    $all_regions = system_region_list($theme_key);

    $theme_settings = array(
      'edit-meta-viewport' => 'edit-meta-viewport',
      'edit-standard-layout' => 'edit-standard-layout',
      'edit-tablet-layout' => 'edit-tablet-layout',
      'edit-mobile-layout' => 'edit-mobile-layout',
      'edit-navbar-container-settings' => 'edit-navbar-container-settings',
      'edit-navbar-margin' => 'edit-navbar-margin',
    );

    foreach ($all_regions as $region_key => $region) {
      $region_id = 'edit-' . str_replace('_', '-', $region_key);

      if (!in_array($region_id, $theme_settings)) {
        $theme_settings[$region_id] = $region_id;
      }
    }

    if (in_array($id, $theme_settings)) {
      $element['#attributes']['class'][] = 'uk-admin-panel-box-light';
    }
  }

  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';

  if (!empty($element['#title'])) {
    $output .= '<h3 class="uk-panel-title uk-admin-panel-title-toggle">';
    $toggle_attributes = array(
      'data-uk-toggle' => "{target:'#" . $id . "-toggle'}",
    );

    $output .= '<a' . drupal_attributes($toggle_attributes) . '>' . $element['#title'] . '</a>';
    $output .= '</h3>';
  }

  $content_attribtues = array(
    'id' => $id . '-toggle',
    'class' => array('uk-admin-panel-content-toggle'),
  );

  if ($collapsed) {
    $content_attribtues['class'][] = 'uk-hidden';
    $content_attribtues['aria-hidden'] = 'true';
  }

  $output .= '<div' . drupal_attributes($content_attribtues) . '>';

  if (!empty($element['#description'])) {
    $output .= '<p class="uk-text-muted">' . $element['#description'] . '</p>';
  }

  $output .= $element['#children'];

  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }

  $output .= '</div>';
  $output .= '</fieldset>';
  return $output;
}

/**
 * Implements theme_fieldset().
 */
function uikit_admin_fieldset__non_collapsible($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id'));
  _form_set_class($element, array());

  $output = '<div' . drupal_attributes($element['#attributes']) . '>';

  if (!empty($element['#title'])) {
    $output .= '<h2>' . $element['#title'] . '</h2>';
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="uk-text-muted">' . $element['#description'] . '</div>';
  }

  $output .= $element['#children'];

  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }

  $output .= '</div>';
  return $output;
}

/**
 * Implements theme_form_element_label().
 */
function uikit_admin_form_element_label__item($variables) {
  $element = $variables['element'];
  $title = !empty($element['#title']) ? filter_xss_admin($element['#title']) : '';

  if ($title) {
    return '<h3>' . $title . '</h3>';
  }
}

/**
 * Implements theme_menu_local_action().
 */
function uikit_admin_menu_local_action($variables) {
  $link = $variables['element']['#link'];
  $link['localized_options']['attributes']['class'][] = 'uk-button';
  $link['localized_options']['attributes']['class'][] = 'uk-button-primary';
  $output = '<li>';

  if (isset($link['href'])) {
    $output .= l($link['title'], $link['href'], isset($link['localized_options']) ? $link['localized_options'] : array());
  }
  elseif (!empty($link['localized_options']['html'])) {
    $output .= $link['title'];
  }
  else {
    $output .= check_plain($link['title']);
  }

  $output .= '</li>';

  return $output;
}

/**
 * Implements theme_menu_local_task().
 */
function uikit_admin_menu_local_task($variables) {
  $link = $variables['element']['#link'];
  $link_text = $link['title'];

  if (!empty($variables['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = '<span class="uk-hidden">' . t('(active tab)') . '</span>';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }

    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
  }

  return '<li' . (!empty($variables['element']['#active']) ? ' class="active uk-active"' : '') . '>' . l($link_text, $link['href'], $link['localized_options']) . "</li>\n";
}

/**
 * Implements theme_node_add_list().
 */
function uikit_admin_node_add_list($variables) {
  $content = $variables['content'];

  if ($content) {
    $output = '<ul class="uk-list uk-list-line uk-admin-list">';

    foreach ($content as $item) {
      $item['localized_options']['attributes']['class'][] = 'uk-text-bold';
      $output .= '<li>';
      $output .= '<i class="uk-icon-chevron-circle-right uk-text-muted uk-display-inline-block uk-admin-vertical-align-top" style="margin-top: 2px"></i>';
      $output .= '<div class="uk-margin-left uk-display-inline-block">';
      $output .= l($item['title'], $item['href'], $item['localized_options']);

      if (isset($item['description'])) {
        $output .= '<div class="uk-text-muted">' . filter_xss_admin($item['description']) . '</div>';
      }

      $output .= '</div>';
      $output .= '</li>';
    }

    $output .= '</ul>';
  }
  else {
    $output .= '<p>' . t('You have not created any content types yet. Go to the <a href="@create-content">content type creation page</a> to add a new content type.', array('@create-content' => url('admin/structure/types/add'))) . '</p>';
  }

  return $output;
}

/**
 * Implements theme_system_themes_page().
 */
function uikit_admin_system_themes_page($variables) {
  $theme_groups = $variables['theme_groups'];

  $output = '<div id="system-themes-page">';

  foreach ($variables['theme_group_titles'] as $state => $title) {
    if (!count($theme_groups[$state])) {
      // Skip this group of themes if no theme is there.
      continue;
    }

    $grid = $state == 'disabled' ? ' uk-grid uk-margin' : ' uk-margin-large-bottom';
    $title_width = $state == 'disabled' ? ' class="uk-width-1-1 uk-margin"' : '';

    // Start new theme group.
    $output .= $state == 'disabled' ? '<div class="uk-grid-divider"></div>' : '';
    $output .= '<div class="system-themes-list system-themes-list-' . $state . $grid . '"><h2' . $title_width . '>' . $title . '</h2>';

    foreach ($theme_groups[$state] as $theme) {
      // Localize the theme description.
      $description = t('@description', array('@description' => $theme->info['description']));

      // Style theme info.
      $notes = count($theme->notes) ? ' (' . implode(', ', $theme->notes) . ')' : '';
      $version = isset($theme->info['version']) ? $theme->info['version'] : '';

      if ($state == 'enabled') {
        $screenshot_variables = array(
          'path' => $theme->screenshot['path'],
          'width' => '294',
          'alt' => $theme->screenshot['alt'],
          'title' => $theme->screenshot['title'],
          'attributes' => array(
            'class' => array('screenshot', 'uk-float-left', 'uk-margin-right'),
          ),
        );

        // Theme the screenshot.
        $screenshot = $theme->screenshot ? theme('image', $screenshot_variables) : '<div class="no-screenshot">' . t('no screenshot') . '</div>';

        $theme->classes[] = 'theme-selector';
        $theme->classes[] = 'uk-margin-bottom';
        $theme->classes[] = 'uk-clearfix';
        $theme_default = in_array('theme-default', $theme->classes) ? ' uk-text-bold' : '';
        $output .= '<div class="' . implode(' ', $theme->classes) . '">';
        $output .= $screenshot;
        $output .= '<div class="theme-info">';
        $output .= '<h3 class="uk-margin-bottom-remove' . $theme_default . '">' . $theme->info['name'] . ' ' . $version . $notes . '</h3>';
        $output .= '<div class="theme-description">' . html_entity_decode($description) . '</div>';

        // Make sure to provide feedback on compatibility.
        if (!empty($theme->incompatible_core)) {
          $output .= '<div class="incompatible">' . t('This version is not compatible with Drupal !core_version and should be replaced.', array('!core_version' => DRUPAL_CORE_COMPATIBILITY)) . '</div>';
        }
        elseif (!empty($theme->incompatible_php)) {
          if (substr_count($theme->info['php'], '.') < 2) {
            $theme->info['php'] .= '.*';
          }
          $output .= '<div class="incompatible">' . t('This theme requires PHP version @php_required and is incompatible with PHP version !php_version.', array(
            '@php_required' => $theme->info['php'],
            '!php_version' => phpversion(),
          )) . '</div>';
        }
        else {
          $output .= theme('links', array(
            'links' => $theme->operations,
            'attributes' => array(
              'class' => array(
                'uk-subnav',
                'uk-subnav-line',
                'uk-margin-remove',
                'uk-admin-theme-operations',
              ),
            ),
          ));
        }
        $output .= '</div></div>';
      }
      else {
        $screenshot_variables = array(
          'path' => $theme->screenshot['path'],
          'width' => '194',
          'alt' => $theme->screenshot['alt'],
          'title' => $theme->screenshot['title'],
          'attributes' => array(
            'class' => array('screenshot'),
          ),
        );

        // Theme the screenshot.
        $screenshot = $theme->screenshot ? theme('image', $screenshot_variables) : '<div class="no-screenshot">' . t('no screenshot') . '</div>';

        $theme->classes[] = 'theme-selector';
        $theme->classes[] = 'uk-width-1-3';
        $theme->classes[] = 'uk-margin';
        $output .= '<div class="' . implode(' ', $theme->classes) . '">';
        $output .= $screenshot;
        $output .= '<div class="theme-info uk-margin-top">';
        $output .= '<h3 class="uk-margin-bottom-remove">' . $theme->info['name'] . ' ' . $version . $notes . '</h3>';
        $output .= '<div class="theme-description">' . html_entity_decode($description) . '</div>';

        // Make sure to provide feedback on compatibility.
        if (!empty($theme->incompatible_core)) {
          $output .= '<div class="incompatible">' . t('This version is not compatible with Drupal !core_version and should be replaced.', array('!core_version' => DRUPAL_CORE_COMPATIBILITY)) . '</div>';
        }
        elseif (!empty($theme->incompatible_php)) {
          if (substr_count($theme->info['php'], '.') < 2) {
            $theme->info['php'] .= '.*';
          }
          $output .= '<div class="incompatible">' . t('This theme requires PHP version @php_required and is incompatible with PHP version !php_version.', array(
            '@php_required' => $theme->info['php'],
            '!php_version' => phpversion(),
          )) . '</div>';
        }
        else {
          $output .= theme('links', array(
            'links' => $theme->operations,
            'attributes' => array(
              'class' => array(
                'uk-subnav',
                'uk-subnav-line',
                'uk-margin-remove',
                'uk-admin-theme-operations',
              ),
            ),
          ));
        }
        $output .= '</div></div>';
      }
    }

    $output .= '</div>';
    $output .= $state == 'disabled' ? '<div class="uk-grid-divider"></div>' : '';
  }
  $output .= '</div>';

  return $output;
}

/**
 * Implements theme_tablesort_indicator().
 */
function uikit_admin_tablesort_indicator($variables) {
  $style = $variables['style'];

  if ($style == 'asc') {
    return '<i class="uk-icon-sort-asc tablesort"></i>';
  }
  else {
    return '<i class="uk-icon-sort-desc tablesort"></i>';
  }
}
